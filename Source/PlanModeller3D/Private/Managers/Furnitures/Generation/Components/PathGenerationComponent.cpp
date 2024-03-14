// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/Components/PathGenerationComponent.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationController.h"
#include "Models/Furnitures/Generation/FurnitureGenerationData.h"


FPathGenerationData UPathGenerationComponent::GetData() const
{
	return ParentController->GetGenerationData().PathComponentData;
}

void UPathGenerationComponent::SetData(const FPathGenerationData& Data) const
{
	auto GenerationData = ParentController->GetGenerationData();
	GenerationData.PathComponentData = Data;
	ParentController->SetGenerationData(GenerationData);
}

TArray<FString> UPathGenerationComponent::GetGeneratedPathesArray() const
{
	return GetData().GeneratedPathes;
}

TArray<FString> UPathGenerationComponent::GetCustomPathesArray() const
{
	return GetData().CustomPathes;
}

bool UPathGenerationComponent::Generate_Implementation()
{
	return Super::Generate_Implementation();
}

bool UPathGenerationComponent::ClearGeneration_Implementation()
{
	return Super::ClearGeneration_Implementation();
}

UPropertiesConstructData* UPathGenerationComponent::GetProperties_Implementation()
{
	return Super::GetProperties_Implementation();
}
