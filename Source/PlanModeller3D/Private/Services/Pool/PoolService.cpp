// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Pool/PoolService.h"
#include "Blueprint/UserWidget.h"
#include "Services/Pool/PoolData.h"
#include "Services/Pool/PoolObject.h"


void UPoolService::Init(const FPoolData& PoolData)
{
	Data = PoolData;
	for (int i = 0; i < Data.InitialSize && i < Data.MaxSize; ++i)
	{
		auto Object = CreateObject();
		HideObject(Object);
		FreePool.Add(Object);
	}
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
}

UObject* UPoolService::GetFromPool()
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
		ShowObject(Object);
		return Object;
	}
	return nullptr;
}

void UPoolService::ReturnToPool(UObject* Object)
{
	if (UsedPool.Contains(Object))
	{
		HideObject(Object);
		UsedPool.Remove(Object);
		FreePool.Add(Object);
	}
}

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

void UPoolService::ShowObject(UObject* Object)
{
	if (Object->IsA(AActor::StaticClass()))
	{
		Cast<AActor>(Object)->SetActorHiddenInGame(false);
	}
	else if (Object->IsA(UUserWidget::StaticClass()))
	{
		Cast<UUserWidget>(Object)->SetVisibility(ESlateVisibility::Visible);
	}

	if (Object->GetClass()->ImplementsInterface(UPoolObject::StaticClass()))
	{
		const auto PoolObject = Cast<IPoolObject>(Object);
		PoolObject->GetFromPool();
	}
}

void UPoolService::HideObject(UObject* Object)
{
	if (Object->IsA(AActor::StaticClass()))
	{
		Cast<AActor>(Object)->SetActorHiddenInGame(true);
	}
	else if (Object->IsA(UUserWidget::StaticClass()))
	{
		Cast<UUserWidget>(Object)->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Object->GetClass()->ImplementsInterface(UPoolObject::StaticClass()))
	{
		const auto PoolObject = Cast<IPoolObject>(Object);
		PoolObject->ReturnToPool();
	}
}

void UPoolService::DestroyObject(UObject* Object)
{
	if (Object->GetClass()->ImplementsInterface(UPoolObject::StaticClass()))
	{
		const auto PoolObject = Cast<IPoolObject>(Object);
		PoolObject->OnPoolDispose();
	}

	if (Object->IsA(AActor::StaticClass()))
	{
		Cast<AActor>(Object)->Destroy();
	}
	else if (Object->IsA(UUserWidget::StaticClass()))
	{
		Cast<UUserWidget>(Object)->RemoveFromParent();
	}
	else
	{
		Object->ConditionalBeginDestroy();
	}
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
