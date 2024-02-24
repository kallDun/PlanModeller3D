// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Models/Material/StoredMaterialData.h"
#include "UObject/Object.h"
#include "MaterialsManagerData.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UMaterialsManagerData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStoredMaterialData> Materials = {};

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("MaterialsManagerData", GetFName());
	}
};
