// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "Managers/Furnitures/Generation/Components/SelectFurnitureGenerationComponent.h"
#include "Models/SaveData/PlanModellerSaveData.h"


void UFurnitureGenerationController::Init_Implementation(UPrimaryDataAsset* Data) { }

void UFurnitureGenerationController::LoadFromSave_Implementation(UPlanModellerSaveData* Save)
{
	ILoadedFromSave::LoadFromSave_Implementation(Save);
	SaveData = Save;

	const auto SelectFurnitureComponent = NewObject<USelectFurnitureGenerationComponent>();
	SelectFurnitureComponent->Initialize(this);
	GenerationComponents.Add(SelectFurnitureComponent);
}

FFurnitureGenerationData UFurnitureGenerationController::GetGenerationData() const
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
			Component->Generate();
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
