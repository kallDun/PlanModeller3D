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
			FurnitureData.GetPoolID(),
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
	SaveData->OnModelChanged.AddDynamic(this, &UFurnitureController::OnModelChanged);
	
	TArray<FString> FurnitureIDsToRemove = {};
	
	for (auto Furniture : Save->Plan3D.Furnitures)
	{
		if (Furniture.Value.IsPreview)
		{
			FurnitureIDsToRemove.Add(Furniture.Key);
			continue;
		}
		CreateFurniture(Furniture.Value, nullptr, Furniture.Key);
		const bool IsCorrectlyPlaced = FurnituresMap[Furniture.Key]->CheckPlacement();
		SaveData->Plan3D.Furnitures[Furniture.Key].IsCorrectlyPlaced = IsCorrectlyPlaced;
		if (!IsCorrectlyPlaced)
		{
			FurnitureIDsToRemove.Add(Furniture.Key);
		}
	}
	
	for (auto ID : FurnitureIDsToRemove)
	{
		SaveData->Plan3D.Furnitures.Remove(ID);
		SaveData->OnModelChanged.Broadcast(ECrudActionType::Delete, EPlanModelType::Furniture, ID);
	}
}

TArray<FFurnitureData> UFurnitureController::GetFurnituresData() const
{
	return Data->Furnitures;
}

TArray<FString> UFurnitureController::GetFurnitureNamesFromData(const TArray<FFurnitureData> List) const
{
	TArray<FString> Names = {};
	for (const FFurnitureData FurnitureData : List)
	{
		Names.Add(FurnitureData.Name);
	}
	return Names;
}

TArray<AFurniture*> UFurnitureController::GetSceneFurnitures(const bool bIncludePreview)
{
	TArray<AFurniture*> SceneFurnitures = {};
	for (auto Furniture : FurnituresMap)
	{
		if (bIncludePreview || !Furniture.Value->SaveModel.IsPreview)
		{
			SceneFurnitures.Add(Furniture.Value);
		}
	}
	return SceneFurnitures;
}

AFurniture* UFurnitureController::GetFurnitureByID(const FString& ID)
{
	return FurnituresMap[ID];
}

void UFurnitureController::DeleteFurniture(const FString& ID) const
{
	SaveData->Plan3D.Furnitures.Remove(ID);
	SaveData->OnModelChanged.Broadcast(ECrudActionType::Delete, EPlanModelType::Furniture, ID);
}

AFurniture* UFurnitureController::CreateFurniture(const FMFurniture& FurnitureModel, AActor* Parent, const FString& Id)
{
	const FFurnitureData* FurnitureData = Data->Furnitures.FindByPredicate([FurnitureModel](const FFurnitureData& PanelData)
	{
		return PanelData.Name == FurnitureModel.Name;
	});
	if (!FurnitureData)
	{
		UE_LOG(LogTemp, Error, TEXT("Furniture with name %s not found"), *FurnitureModel.Name);
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
	if (!SaveData->Plan3D.Furnitures.Contains(ObjectId)) return;
	
	if (ActionType == ECrudActionType::Create)
	{
		CreateFurniture(SaveData->Plan3D.Furnitures[ObjectId], nullptr, ObjectId);
		SaveData->Plan3D.Furnitures[ObjectId].IsCorrectlyPlaced = FurnituresMap[ObjectId]->CheckPlacement();
	}
	else if (ActionType == ECrudActionType::Delete)
	{
		if (FurnituresMap.Contains(ObjectId))
		{
			DestroyFurniture(FurnituresMap[ObjectId]);
		}
	}
	else if (ActionType == ECrudActionType::Update)
	{
		if (FurnituresMap.Contains(ObjectId))
		{
			FurnituresMap[ObjectId]->UpdateView(SaveData->Plan3D.Furnitures[ObjectId]);
			SaveData->Plan3D.Furnitures[ObjectId].IsCorrectlyPlaced = FurnituresMap[ObjectId]->CheckPlacement();
		}
		else
		{
			CreateFurniture(SaveData->Plan3D.Furnitures[ObjectId], nullptr, ObjectId);
			SaveData->Plan3D.Furnitures[ObjectId].IsCorrectlyPlaced = FurnituresMap[ObjectId]->CheckPlacement();
		}
	}
}
