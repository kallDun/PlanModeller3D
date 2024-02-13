// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PMCharacter.h"
#include "PMSpectatorCharacter.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APMSpectatorCharacter : public APMCharacter
{
	GENERATED_BODY()

protected:
	APMSpectatorCharacter() : APMCharacter() { }

public:
	virtual UPropertiesConstructData* GetProperties_Implementation() override;
};
