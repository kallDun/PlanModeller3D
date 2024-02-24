// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/FurnitureController.h"
#include "Services/Pool/PoolData.h"
#include "Core/CoreFunctionLib.h"
#include "Actors/Furnitures/Furniture.h"
#include "Managers/Furnitures/FurnitureControllerData.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Services/Pool/PoolService.h"
#include "Services/Pool/PoolsSystem.h"


void UFurnitureController::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UFurnitureControllerData>(DataAsset);
	PoolsSystem = UCoreFunctionLib::GetPoolsSystem(this);

	for (FFurnitureData FurnitureData : Data->Furnitures)
	{
		const FPoolData PoolData = FPoolData(
			FurnitureData.UseNameAsPoolID ? FurnitureData.Name : FurnitureData.PoolID,
			FurnitureData.FurnitureClass,
			Data->InitPoolSizeForOneFurniture, Data->MaxPoolSizeForOneFurniture,
			ELevelTransitionPoolBehaviour::Dispose,
			EPoolRule::None, 0,
			EPoolRule::MultiplyByTwo, 2,
			EPoolInitializationType::Lazy);
			
		PoolsSystem->CreatePool(PoolData);
	}
}

void UFurnitureController::LoadFromSave_Implementation(UPlanModellerSaveData* Save)
{
	ILoadedFromSave::LoadFromSave_Implementation(Save);
	SaveData = Save;
	for (auto Furniture : Save->Plan3D.Furnitures)
	{
		CreateFurniture(Furniture.Value, nullptr, Furniture.Key);
	}
	SaveData->OnModelChanged.AddDynamic(this, &UFurnitureController::OnModelChanged);
}

AFurniture* UFurnitureController::CreateFurniture(const FMFurniture& FurnitureModel, AActor* Parent, const FString& Id)
{
	auto Name = FurnitureModel.Name;
	const FFurnitureData* FurnitureData = Data->Furnitures.FindByPredicate([Name](const FFurnitureData& PanelData)
	{
		return PanelData.Name == Name;
	});
	if (!FurnitureData)
	{
		UE_LOG(LogTemp, Error, TEXT("Furniture with name %s not found"), *Name.ToString());
		return nullptr;
	}

	const auto Pool = PoolsSystem->GetPool(FurnitureData->GetPoolID());
	if (!Pool)
	{
		UE_LOG(LogTemp, Error, TEXT("Pool with name %s not found"), *FurnitureData->GetPoolID().ToString());
		return nullptr;
	}

	AFurniture* Furniture = Cast<AFurniture>(Pool->GetFromPool(Parent));
	if (Furniture)
	{
		Furniture->Init(*FurnitureData, FurnitureModel, Id);
		FurnituresMap.Add(Furniture->ID, Furniture);
	}
	return Furniture;
}

void UFurnitureController::DestroyFurniture(AFurniture* Furniture)
{
	const auto Pool = PoolsSystem->GetPool(Furniture->Data.GetPoolID());
	Pool->ReturnToPool(Furniture);
	FurnituresMap.Remove(Furniture->ID);
}

void UFurnitureController::OnModelChanged(ECrudActionType ActionType, EPlanModelType ModelType, FString ObjectId)
{
	if (ModelType != EPlanModelType::Furniture) return;
	
	if (ActionType == ECrudActionType::Create)
	{
		CreateFurniture(SaveData->Plan3D.Furnitures[ObjectId], nullptr, ObjectId);
	}
	else if (ActionType == ECrudActionType::Delete)
	{
		DestroyFurniture(FurnituresMap[ObjectId]);
	}
	else if (ActionType == ECrudActionType::Update)
	{
		FurnituresMap[ObjectId]->UpdateView(SaveData->Plan3D.Furnitures[ObjectId]);
	}
}
