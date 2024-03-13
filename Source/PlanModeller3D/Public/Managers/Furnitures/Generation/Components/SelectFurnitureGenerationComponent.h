// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"
#include "Models/Furnitures/Generation/SelectFurnitureGenerationData.h"
#include "SelectFurnitureGenerationComponent.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API USelectFurnitureGenerationComponent : public UFurnitureGenerationComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	FSelectFurnitureGenerationData GetData() const;

	UFUNCTION()
	void SetData(const FSelectFurnitureGenerationData& Data) const;

public:
	virtual bool Generate_Implementation() override;

	virtual bool ClearGeneration_Implementation() override;

	virtual UPropertiesConstructData* GetProperties_Implementation() override;
};
