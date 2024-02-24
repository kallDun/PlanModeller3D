// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Models/Material/SavedMaterialData.h"
#include "MWall.generated.h"

USTRUCT(BlueprintType)
struct FMWall
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSavedMaterialData> Materials = {};
	
};
