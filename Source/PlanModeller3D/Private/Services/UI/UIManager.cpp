// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CoreFunctionLib.h"
#include "Services/Pool/PoolData.h"
#include "Services/Pool/PoolService.h"
#include "Services/Pool/PoolsSystem.h"
#include "Services/UI/ManagerUI.h"
#include "Services/UI/ManagerUIData.h"
#include "Services/UI/PanelUI.h"


void UManagerUI::Init_Implementation(UPrimaryDataAsset* ManagerData)
{
	IInitializable::Init_Implementation(ManagerData);
	
	Data = Cast<UManagerUIData>(ManagerData);
	PoolsSystem = UCoreFunctionLib::GetPoolsSystem(this); 

	for (auto PanelData : Data->Panels)
	{
		const FPoolData PoolData = FPoolData(PanelData.UseNameAsPoolID ? PanelData.Name : PanelData.PoolID,
			PanelData.PanelClass, 1, PanelData.bIsSingleton ? 1 : PanelData.MaxCount,
			PanelData.LevelTransitionBehaviour,
			EPoolRule::None, 0,
			EPoolRule::AddConstant, 1,
			EPoolInitializationType::Lazy);
		PoolsSystem->CreatePool(PoolData);
	}
}

UPanelUI* UManagerUI::GetPanel(FName PanelName, UObject* Parent) const
{
	const FPanelUIData* PanelData = Data->Panels.FindByPredicate([PanelName](const FPanelUIData& PanelData)
	{
		return PanelData.Name == PanelName;
	});
	if (!PanelData)
	{
		UE_LOG(LogTemp, Error, TEXT("Panel with name %s not found"), *PanelName.ToString());
		return nullptr;
	}

	const auto PoolID = PanelData->UseNameAsPoolID ? PanelData->Name : PanelData->PoolID;
	const auto Pool = PoolsSystem->GetPool(PoolID);
	if (!Pool)
	{
		UE_LOG(LogTemp, Error, TEXT("Pool with name %s not found"), *PoolID.ToString());
		return nullptr;
	}

	if (PanelData->bIsSingleton && Pool->GetUsedCount() > 0)
	{
		switch (PanelData->ActionOnGetSingletonPanel)
		{
			case EActionOnGetSingletonPanel::None:
				UE_LOG(LogTemp, Error, TEXT("Panel with name %s already exists"), *PanelName.ToString());
				return nullptr;
			
			case EActionOnGetSingletonPanel::DoNothing:
				return nullptr;
			
			case EActionOnGetSingletonPanel::ReturnAndGetPanel:
				Pool->ReturnToPool(Pool->GetUsedPool()[0]);
				return Cast<UPanelUI>(Pool->GetFromPool(Parent));

			case EActionOnGetSingletonPanel::ReturnOld:
				return Cast<UPanelUI>(Pool->GetUsedPool()[0]);
		}
	}
	return Cast<UPanelUI>(Pool->GetFromPool(Parent));
}

void UManagerUI::ReturnPanel(UPanelUI* Panel) const
{
	const FPanelUIData* PanelData = Data->Panels.FindByPredicate([Panel](const FPanelUIData& PanelData)
	{
		return PanelData.PanelClass.Get() == Panel->GetClass();
	});
	if (!PanelData)
	{
		UE_LOG(LogTemp, Error, TEXT("Panel in pool with class %s not found"), *Panel->GetClass()->GetName());
		return;
	}

	const auto Pool = PoolsSystem->GetPool(PanelData->UseNameAsPoolID ? PanelData->Name : PanelData->PoolID);
	if (!Pool)
	{
		UE_LOG(LogTemp, Error, TEXT("Pool with name %s not found"), *PanelData->PoolID.ToString());
		return;
	}

	Pool->ReturnToPool(Panel);
}
