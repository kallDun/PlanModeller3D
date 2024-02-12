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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta=(ClampMin=0f, ClampMax=180f))
	float CameraFOV = 90.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta=(ClampMin=0f, ClampMax=100f))
	float CameraSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bIsColliding = false;

	virtual void SelectAsCurrent_Implementation() override;

	virtual void OnDeselect_Implementation() override;
	
	virtual UPropertiesConstructData* GetProperties_Implementation() override;

private:
	UFUNCTION() double GetCameraFOV() { return CameraFOV; }
	UFUNCTION() void SetCameraFOV(const double Value) { CameraFOV = Value; }

	UFUNCTION() double GetCameraSpeed() { return CameraSpeed; }
	UFUNCTION() void SetCameraSpeed(const double Value) { CameraSpeed = Value; }

	UFUNCTION() bool GetIsColliding() { return bIsColliding; }
	UFUNCTION() void SetIsColliding(const bool bValue) { bIsColliding = bValue; }
	
};
