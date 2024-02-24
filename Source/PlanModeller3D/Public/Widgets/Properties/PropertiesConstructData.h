// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoolPropertyConstructObject.h"
#include "MaterialPropertyConstructObject.h"
#include "NumberPropertyConstructObject.h"
#include "SceneObjectPropertyConstructObject.h"
#include "TextPropertyConstructObject.h"
#include "UObject/Object.h"
#include "PropertiesConstructData.generated.h"

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPropertiesConstructData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FNumberPropertyConstructObject> NumberProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTextPropertyConstructObject> TextProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBoolPropertyConstructObject> BoolProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSceneObjectPropertyConstructObject> SceneObjectProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMaterialPropertyConstructObject> MaterialProperties = {};
};
