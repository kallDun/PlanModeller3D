// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PropertiesFactoryData.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UPropertiesFactoryData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TextPropertyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoolPropertyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NumberPropertyName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SceneObjectPropertyName;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("PropertiesFactoryData", GetFName());
	}
};
