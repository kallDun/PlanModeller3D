// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PMCharacter.generated.h"

class UPMCharacterCamera;

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API APMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APMCharacter() = default;

	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	TArray<UPMCharacterCamera*> Cameras = {};

	UFUNCTION()
	UPMCharacterCamera* GetCurrentCamera() const;

	UFUNCTION(BlueprintNativeEvent)
	void ResetSettingsToDefault();
};