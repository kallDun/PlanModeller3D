// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelType.h"
#include "UObject/Object.h"
#include "LevelTransitionData.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API ULevelTransitionData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ELevelType, FName> LevelPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELevelType InitialLevelType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LoadingScreenName;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("LevelTransitionData", GetFName());
	}
};
