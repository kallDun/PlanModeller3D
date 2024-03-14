// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "PlaceFurnitureGenerationComponent.generated.h"

struct FPlacedFurnitureGenerationData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPlaceFurnitureGenerationComponent : public UFurnitureGenerationComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	FPlacedFurnitureGenerationData GetData() const;

	UFUNCTION()
	void SetData(const FPlacedFurnitureGenerationData& Data) const;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Generation")
	TArray<FString> GetGeneratedFurnitureArray() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Generation")
	TArray<FString> GetCustomFurnitureArray() const;

public:
	virtual bool Generate_Implementation() override;

	virtual bool ClearGeneration_Implementation() override;

	virtual UPropertiesConstructData* GetProperties_Implementation() override;
};
