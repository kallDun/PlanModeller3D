// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PMCharacterCamera.generated.h"


class UPropertiesConstructData;

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API UPMCharacterCamera : public UActorComponent
{
	GENERATED_BODY()

public:
	UPMCharacterCamera() = default;

	UPROPERTY(BlueprintReadOnly)
	class APMCharacter* Character;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	FName CameraName;

	UPROPERTY(EditAnywhere, Category = "Properties")
	bool bIsDefaultCamera = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCurrentCamera = false;

public:
	UFUNCTION(BlueprintCallable)
	void Init(APMCharacter* InCharacter);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SelectCameraAsCurrent();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeselectCamera();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPropertiesConstructData* GetProperties(); 
};
