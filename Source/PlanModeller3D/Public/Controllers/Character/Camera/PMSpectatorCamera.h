// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PMCharacterCamera.h"
#include "PMSpectatorCamera.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLANMODELLER3D_API UPMSpectatorCamera : public UPMCharacterCamera
{
	GENERATED_BODY()

public:
	UPMSpectatorCamera() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta=(ClampMin=0f, ClampMax=180f))
	float CameraFOV = 90.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta=(ClampMin=0f))
	float CameraSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bIsColliding = false;

	virtual void SelectCameraAsCurrent_Implementation() override;

	virtual void OnDeselectCamera_Implementation() override;
	
};
