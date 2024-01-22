// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Initializable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UInitializable : public UInterface
{
	GENERATED_BODY()
};

class PLANMODELLER3D_API IInitializable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization")
	void Init(UPrimaryDataAsset* Data);
	
};
