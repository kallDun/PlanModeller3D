// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Pool/PoolService.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Level/LevelTransitionController.h"
#include "Services/Pool/PoolData.h"
#include "Services/Pool/PoolObject.h"


void UPoolService::Init(const FPoolData& PoolData)
{
	TransitionController = UCoreFunctionLib::GetTransitionController(this);
	Data = PoolData;
	for (int i = 0; i < Data.InitialSize && i < Data.MaxSize; ++i)
	{
		auto Object = CreateObject();
		HideObject(Object);
		FreePool.Add(Object);
	}
	
	TransitionController->OnLevelUnloadedEvent.AddDynamic(this, &UPoolService::OnLevelUnloaded);
	TransitionController->OnLevelLoadedEvent.AddDynamic(this, &UPoolService::OnLevelLoaded);
}

void UPoolService::Dispose()
{
	for (const auto Object : UsedPool)
	{
		DestroyObject(Object);
	}
	for (const auto Object : FreePool)
	{
		DestroyObject(Object);
	}
	UsedPool.Empty();

	TransitionController->OnLevelUnloadedEvent.RemoveDynamic(this, &UPoolService::OnLevelUnloaded);
	TransitionController->OnLevelLoadedEvent.RemoveDynamic(this, &UPoolService::OnLevelLoaded);
}

// PUBLIC

UObject* UPoolService::GetFromPool(UObject* Parent)
{
	IncreasePoolSize(Data.GetFromPoolRule, Data.GetFromPoolRuleConstant);
	if (FreePool.Num() > 0)
	{
		UObject* Object = FreePool.Pop();
		UsedPool.Add(Object);
		if (FreePool.Num() == 0)
		{
			IncreasePoolSize(Data.CloseToMaxSizeRule, Data.CloseToMaxSizeRuleConstant);
		}
		ShowObject(Object, Parent);
		return Object;
	}
	return nullptr;
}

void UPoolService::ReturnToPool(UObject* Object)
{
	if (UsedPool.Contains(Object))
	{
		UsedPool.Remove(Object);
		FreePool.Add(Object);
		HideObject(Object);
	}
}

int UPoolService::GetUsedCount() const
{
	return UsedPool.Num();
}

TArray<UObject*> UPoolService::GetUsedPool() const
{
	return TArray(UsedPool);
}

// PRIVATE

UObject* UPoolService::CreateObject()
{
	if (Data.Class == nullptr)
	{
		return nullptr;
	}
	// if actor
	if (Data.Class->IsChildOf(AActor::StaticClass()))
	{
		return GetWorld()->SpawnActor(Data.Class);
	}
	// if widget
	if (Data.Class->IsChildOf(UUserWidget::StaticClass()))
	{
		return CreateWidget<UUserWidget>(GetWorld(), TSubclassOf<UUserWidget>(Data.Class));
	}
	// else if object
	return NewObject<UObject>(this, Data.Class);
}

void UPoolService::ShowObject(UObject* Object, UObject* Parent, const bool BroadcastMessage)
{
	if (Object->IsA(AActor::StaticClass()))
	{
		const auto Actor = Cast<AActor>(Object);
		Actor->SetActorHiddenInGame(false);
		if (Parent != nullptr)
		{
			Actor->AttachToActor(Cast<AActor>(Parent), FAttachmentTransformRules::KeepRelativeTransform);
			Actor->SetOwner(Cast<AActor>(Parent));
		}
	}
	else if (Object->IsA(UUserWidget::StaticClass()))
	{
		const auto Widget = Cast<UUserWidget>(Object);
		Widget->SetVisibility(ESlateVisibility::Visible);
		if (Parent != nullptr)
		{
			if (Parent->IsA(UPanelWidget::StaticClass()))
			{
				const auto Panel = Cast<UPanelWidget>(Parent);
				Panel->AddChild(Widget);
			}
		}
		else
		{
			Widget->AddToViewport();
		}
	}

	if (BroadcastMessage && Object->GetClass()->ImplementsInterface(UPoolObject::StaticClass()))
	{
		const auto PoolObject = Cast<IPoolObject>(Object);
		PoolObject->Execute_GetFromPool(Object, this);
	}
}

void UPoolService::HideObject(UObject* Object, const bool BroadcastMessage)
{
	if (Object->IsA(AActor::StaticClass()))
	{
		const auto Actor = Cast<AActor>(Object);
		Actor->SetActorHiddenInGame(true);
		Actor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Actor->SetOwner(nullptr);
	}
	else if (Object->IsA(UUserWidget::StaticClass()))
	{
		const auto Widget = Cast<UUserWidget>(Object);
		Widget->SetVisibility(ESlateVisibility::Collapsed);
		Widget->RemoveFromParent();
	}

	if (BroadcastMessage && Object->GetClass()->ImplementsInterface(UPoolObject::StaticClass()))
	{
		const auto PoolObject = Cast<IPoolObject>(Object);
		PoolObject->Execute_ReturnToPool(Object, this);
	}
}

void UPoolService::DestroyObject(UObject* Object)
{
	if (Object->GetClass()->ImplementsInterface(UPoolObject::StaticClass()))
	{
		const auto PoolObject = Cast<IPoolObject>(Object);
		PoolObject->Execute_OnPoolDispose(Object,this);
	}

	if (Object->IsA(AActor::StaticClass()))
	{
		Cast<AActor>(Object)->Destroy();
	}
	Object->ConditionalBeginDestroy();
}

void UPoolService::IncreasePoolSize(const EPoolRule Rule, const int Constant)
{
	if (Rule == EPoolRule::None) return;
	
	const int CurrentSize = UsedPool.Num() + FreePool.Num();
	if (CurrentSize >= Data.MaxSize) return;

	int IncreaseBy;

	switch (Rule)
	{
		case EPoolRule::AddOne:
			IncreaseBy = FMath::Clamp(CurrentSize + 1, 0, Data.MaxSize) - CurrentSize;
			break;
		case EPoolRule::AddConstant:
			IncreaseBy = FMath::Clamp(CurrentSize + Constant, 0, Data.MaxSize) - CurrentSize;
			break;
		case EPoolRule::MultiplyByTwo:
			IncreaseBy = FMath::Clamp(CurrentSize * 2, 0, Data.MaxSize) - CurrentSize;
			break;
		case EPoolRule::MultiplyByConstant:
			IncreaseBy = FMath::Clamp(CurrentSize * Constant, 0, Data.MaxSize) - CurrentSize;
			break;
		default: return;
	}
	for (int i = 0; i < IncreaseBy; ++i)
	{
		auto Object = CreateObject();
		HideObject(Object);
		FreePool.Add(Object);
	}
}

// EVENT HANDLERS

void UPoolService::OnLevelUnloaded(ELevelType Level)
{
	if (Data.LevelTransitionBehaviour == ELevelTransitionPoolBehaviour::Dispose)
	{
		Dispose();
	}
	else if (Data.LevelTransitionBehaviour == ELevelTransitionPoolBehaviour::Hide)
	{
		for (const auto Object : UsedPool)
		{
			HideObject(Object, false);
			FreePool.Add(Object);
		}
		UsedPool.Empty();
	}
	else if (Data.LevelTransitionBehaviour == ELevelTransitionPoolBehaviour::HideThenShow)
	{
		for (const auto Object : UsedPool)
		{
			HideObject(Object, false);
		}
	}
}

void UPoolService::OnLevelLoaded(ELevelType Level)
{
	if (Data.LevelTransitionBehaviour == ELevelTransitionPoolBehaviour::HideThenShow)
	{
		for (const auto Object : UsedPool)
		{
			ShowObject(Object, nullptr, false);
		}
	}
}
