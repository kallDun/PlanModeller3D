// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MFurniture.generated.h"

USTRUCT(BlueprintType)
struct FMFurniture
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int VariationIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCorrectlyPlaced;
};
