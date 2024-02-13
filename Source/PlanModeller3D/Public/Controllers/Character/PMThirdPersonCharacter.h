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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta=(ClampMin=0f, ClampMax=180f))
	float CameraFOV = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta=(ClampMin=0f, ClampMax=180f))
	FString RoomID;
	
	virtual UPropertiesConstructData* GetProperties_Implementation() override;

	virtual void ResetStartLocationAndRotation_Implementation() override;

private:
	UFUNCTION() double GetCameraFOV() { return CameraFOV; }
	UFUNCTION() void SetCameraFOV(const double Value)
	{
		CameraFOV = Value;
		OnUpdateProperties();
	}	
};
