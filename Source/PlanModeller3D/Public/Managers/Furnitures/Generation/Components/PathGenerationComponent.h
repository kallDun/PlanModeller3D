// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "PathGenerationComponent.generated.h"

struct FPlacedFurnitureGenerationData;
struct FPathGenerationData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPathGenerationComponent : public UFurnitureGenerationComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	FPathGenerationData GetData() const;

	UFUNCTION()
	void SetData(const FPathGenerationData& Data) const;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Generation")
	TArray<FString> GetGeneratedPathesArray() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Generation")
	TArray<FString> GetCustomPathesArray() const;

public:
	virtual bool Generate_Implementation() override;

	virtual bool ClearGeneration_Implementation() override;

	virtual UPropertiesConstructData* GetProperties_Implementation() override;
};
