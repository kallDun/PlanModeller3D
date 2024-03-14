// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/Components/PlaceFurnitureGenerationComponent.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Models/Furnitures/Generation/FurnitureGenerationData.h"


FPlacedFurnitureGenerationData UPlaceFurnitureGenerationComponent::GetData() const
{
	return ParentController->GetGenerationData().PlacedFurnitureComponentData;
}

void UPlaceFurnitureGenerationComponent::SetData(const FPlacedFurnitureGenerationData& Data) const
{
	auto GenerationData = ParentController->GetGenerationData();
	GenerationData.PlacedFurnitureComponentData = Data;
	ParentController->SetGenerationData(GenerationData);
}

TArray<FString> UPlaceFurnitureGenerationComponent::GetGeneratedFurnitureArray() const
{
	return GetData().GeneratedFurnitureNames;
}

TArray<FString> UPlaceFurnitureGenerationComponent::GetCustomFurnitureArray() const
{
	return GetData().CustomFurnitureNames;
}

bool UPlaceFurnitureGenerationComponent::Generate_Implementation()
{
	return Super::Generate_Implementation();
}

bool UPlaceFurnitureGenerationComponent::ClearGeneration_Implementation()
{
	return Super::ClearGeneration_Implementation();
}

UPropertiesConstructData* UPlaceFurnitureGenerationComponent::GetProperties_Implementation()
{
	return Super::GetProperties_Implementation();
}
