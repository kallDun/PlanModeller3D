// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PMCharacter.h"
#include "PMThirdPersonCharacter.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APMThirdPersonCharacter : public APMCharacter
{
	GENERATED_BODY()

protected:
	APMThirdPersonCharacter() : APMCharacter() { }

public:
	virtual UPropertiesConstructData* GetProperties_Implementation() override;

	virtual void ResetStartLocationAndRotation_Implementation() override;
};
