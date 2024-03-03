// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Models/Instrument/SceneObjectSelection.h"
#include "SelectionConverterLib.generated.h"


UCLASS()
class PLANMODELLER3D_API USelectionConverterLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Converter")
	static FSceneObjectSelection ConvertToSelectionFromActor(AActor* Actor, uint8 AvailableSelections);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Converter", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static AActor* ConvertToActorFromSelection(const UObject* WorldContextObject, FSceneObjectSelection Selection);
};
