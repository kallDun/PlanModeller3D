// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Models/Material/SavedMaterialData.h"

#include "MRoom.generated.h"

USTRUCT(BlueprintType)
struct FMRoom
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSavedMaterialData Material;
	
};
