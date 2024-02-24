// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PMCharacter.h"
#include "PMFirstPersonCharacter.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APMFirstPersonCharacter : public APMCharacter
{
	GENERATED_BODY()

protected:
	APMFirstPersonCharacter() : APMCharacter() { }

public:	
	virtual UPropertiesConstructData* GetProperties_Implementation() override;

	virtual void ResetStartLocationAndRotation_Implementation() override;
};
