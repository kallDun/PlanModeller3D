// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorSelectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UActorSelectable : public UInterface
{
	GENERATED_BODY()
};


class PLANMODELLER3D_API IActorSelectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ActorSelectable")
	void ShowSelectionPreview();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ActorSelectable")
	void HideSelectionPreview();
	
};
