// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorHighlightable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UActorHighlightable : public UInterface
{
	GENERATED_BODY()
};


class PLANMODELLER3D_API IActorHighlightable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ActorHighlightable")
	void Highlight(float Duration);
	
};
