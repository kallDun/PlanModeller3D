// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/Components/SelectFurnitureGenerationComponent.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Models/Furnitures/Generation/FurnitureGenerationData.h"


FSelectFurnitureGenerationData USelectFurnitureGenerationComponent::GetData() const
{
	return ParentController->GetGenerationData().SelectFurnitureComponentData;
}

void USelectFurnitureGenerationComponent::SetData(const FSelectFurnitureGenerationData& Data) const
{
	auto GenerationData = ParentController->GetGenerationData();
	GenerationData.SelectFurnitureComponentData = Data;
	ParentController->SetGenerationData(GenerationData);
}

bool USelectFurnitureGenerationComponent::Generate_Implementation()
{
	return Super::Generate_Implementation();
}

bool USelectFurnitureGenerationComponent::ClearGeneration_Implementation()
{
	return Super::ClearGeneration_Implementation();
}

UPropertiesConstructData* USelectFurnitureGenerationComponent::GetProperties_Implementation()
{
	return Super::GetProperties_Implementation();
}
