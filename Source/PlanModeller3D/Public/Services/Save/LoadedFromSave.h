// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LoadedFromSave.generated.h"

class UPlanModellerSaveData;

UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class ULoadedFromSave : public UInterface
{
	GENERATED_BODY()
};

class PLANMODELLER3D_API ILoadedFromSave
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LoadFromSave(UPlanModellerSaveData* Save);
	
};
