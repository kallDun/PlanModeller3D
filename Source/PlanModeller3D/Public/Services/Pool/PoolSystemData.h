// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolData.h"
#include "Engine/DataAsset.h"
#include "PoolSystemData.generated.h"

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPoolSystemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPoolData> Pools;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("PoolSystemData", GetFName());
	}
};
