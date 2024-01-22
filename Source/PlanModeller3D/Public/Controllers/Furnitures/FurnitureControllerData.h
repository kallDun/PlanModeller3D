// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Models/Furnitures/FurnitureData.h"
#include "UObject/Object.h"
#include "FurnitureControllerData.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UFurnitureControllerData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFurnitureData> Furnitures;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("FurnitureControllerData", GetFName());
	}
};
