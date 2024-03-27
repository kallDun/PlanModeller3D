// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "Managers/Furnitures/Generation/Components/SelectFurnitureGenerationComponent.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void UFurnitureGenerationController::Init_Implementation(UPrimaryDataAsset* Data) { }

void UFurnitureGenerationController::LoadFromSave_Implementation(UPlanModellerSaveData* Save)
{
	ILoadedFromSave::LoadFromSave_Implementation(Save);
	SaveData = Save;

	const auto SelectFurnitureComponent = NewObject<USelectFurnitureGenerationComponent>();
	SelectFurnitureComponent->Initialize(this);
	GenerationComponents.Add(SelectFurnitureComponent);
}

FFurnitureGenerationData& UFurnitureGenerationController::GetGenerationData() const
{
	return SaveData->Plan3D.FurnitureGenerationData;
}

void UFurnitureGenerationController::SetGenerationData(const FFurnitureGenerationData& Data) const
{
	SaveData->Plan3D.FurnitureGenerationData = Data;
}

void UFurnitureGenerationController::GenerateAll()
{
	for (const auto Component : GenerationComponents)
	{
		if (!Component->IsEmpty())
		{
			Component->StartGeneration();
		}
	}
}

void UFurnitureGenerationController::ClearAll()
{
	for (const auto Component : GenerationComponents)
	{
		Component->ClearGeneration();
	}
}

UPropertiesConstructData* UFurnitureGenerationController::GetProperties_Implementation()
{
	const auto Properties = NewObject<UPropertiesConstructData>();

	FOnGetSceneObjectValue GetRoom = FOnGetSceneObjectValue();
	GetRoom.BindDynamic(this, &UFurnitureGenerationController::GetRoom);
	FOnSetSceneObjectValue SetRoom = FOnSetSceneObjectValue();
	SetRoom.BindDynamic(this, &UFurnitureGenerationController::SetRoom);
	Properties->SceneObjectProperties.Add(FSceneObjectPropertyConstructObject(
		0, FText::FromString("Room"), static_cast<uint8>(EInstrumentAvailableSelection::IAS_Room), GetRoom, SetRoom));
	
	return Properties;
}
