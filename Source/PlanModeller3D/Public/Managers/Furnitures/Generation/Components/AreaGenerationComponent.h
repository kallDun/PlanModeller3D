// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "AreaGenerationComponent.generated.h"

struct FPlacedFurnitureGenerationData;
struct FAreaGenerationData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UAreaGenerationComponent : public UFurnitureGenerationComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	FAreaGenerationData GetData() const;

	UFUNCTION()
	void SetData(const FAreaGenerationData& Data) const;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Generation")
	TArray<FString> GetGeneratedAreasArray() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Generation")
	TArray<FString> GetCustomAreasArray() const;

public:
	virtual bool StartGeneration_Implementation() override;

	virtual bool ClearGeneration_Implementation() override;

	virtual UPropertiesConstructData* GetProperties_Implementation() override;
};
