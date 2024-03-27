// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/Components/AreaGenerationComponent.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Models/Furnitures/Generation/FurnitureGenerationData.h"


FAreaGenerationData UAreaGenerationComponent::GetData() const
{
	return ParentController->GetGenerationData().AreaComponentData;
}

void UAreaGenerationComponent::SetData(const FAreaGenerationData& Data) const
{
	auto GenerationData = ParentController->GetGenerationData();
	GenerationData.AreaComponentData = Data;
	ParentController->SetGenerationData(GenerationData);
}

TArray<FString> UAreaGenerationComponent::GetGeneratedAreasArray() const
{
	return GetData().GeneratedAreas;
}

TArray<FString> UAreaGenerationComponent::GetCustomAreasArray() const
{
	return GetData().CustomAreas;
}

bool UAreaGenerationComponent::StartGeneration_Implementation()
{
	return Super::StartGeneration_Implementation();
}

bool UAreaGenerationComponent::ClearGeneration_Implementation()
{
	return Super::ClearGeneration_Implementation();
}

UPropertiesConstructData* UAreaGenerationComponent::GetProperties_Implementation()
{
	return Super::GetProperties_Implementation();
}
