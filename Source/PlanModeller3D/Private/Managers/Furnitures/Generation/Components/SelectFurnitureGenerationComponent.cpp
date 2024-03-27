// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/Components/SelectFurnitureGenerationComponent.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Managers/Furnitures/Generation/Components/Algorithms/SelectFurnitureGenerationAlgorithm.h"
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

TArray<FSelectedFurnitureData> USelectFurnitureGenerationComponent::GetGeneratedFurnitureArray() const
{
	return GetData().GeneratedFurniture;
}

TArray<FSelectedFurnitureData> USelectFurnitureGenerationComponent::GetCustomFurnitureArray() const
{
	return GetData().CustomFurniture;
}

bool USelectFurnitureGenerationComponent::StartGeneration_Implementation()
{
	if (Super::StartGeneration_Implementation() == false) return false;
	SelectFurnitureGenerationAlgorithm Algorithm = SelectFurnitureGenerationAlgorithm();
	Algorithm.OnGenerationFinished.BindUFunction(this, "OnGenerationFinished");
	GenerationThread = FRunnableThread::Create(&Algorithm, TEXT("SelectFurnitureGenerationAlgorithm"));
	GenerationStatus = ERunnableStatus::Running;
	OnGenerationComponentViewUpdated.Broadcast(this);
	return true;
}

bool USelectFurnitureGenerationComponent::ClearGeneration_Implementation()
{
	return Super::ClearGeneration_Implementation();
}

UPropertiesConstructData* USelectFurnitureGenerationComponent::GetProperties_Implementation()
{
	return Super::GetProperties_Implementation();
}
