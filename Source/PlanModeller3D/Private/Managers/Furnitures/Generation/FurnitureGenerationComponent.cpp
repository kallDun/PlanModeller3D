// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "Widgets/Properties/PropertiesConstructData.h"


bool UFurnitureGenerationComponent::StartGeneration_Implementation()
{
	for (const auto Component : RequiredComponentsToGenerate)
	{
		if (Component->IsEmpty()) return false;
	}
	return true;
}

bool UFurnitureGenerationComponent::ClearGeneration_Implementation()
{
	if (IsEmpty()) return false;
	return true;
}

UPropertiesConstructData* UFurnitureGenerationComponent::GetProperties_Implementation()
{
	return NewObject<UPropertiesConstructData>();
}

void UFurnitureGenerationComponent::OnGenerationFinished(const ERunnableStatus Status)
{
	GenerationStatus = Status;
	OnGenerationComponentViewUpdated.Broadcast(this);
}
