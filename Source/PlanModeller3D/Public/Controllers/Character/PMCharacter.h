// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSettings.h"
#include "GameFramework/Character.h"
#include "PMCharacter.generated.h"

class UPropertiesConstructData;

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API APMCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	APMCharacter() { }

	UPROPERTY(BlueprintReadOnly)
	class USavingService* SavingService;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PM Character")
	FName CharacterName;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "PM Character")
	class UCharactersManager* Manager;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "PM Character")
	class UInputMappingContext* PlayerInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "PM Character")
	FCharacterSettings DefaultSettings;

// GETTERS & SETTERS	
protected:
	UFUNCTION(BlueprintCallable)
	FCharacterSettings& GetCharacterSettings() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterSettings(const FCharacterSettings& InSettings) const;

	UFUNCTION() double GetCameraFOV() { return GetCharacterSettings().CameraFOV; }
	UFUNCTION() void SetCameraFOV(const double Value)
	{
		GetCharacterSettings().CameraFOV = Value;
		OnUpdateProperties();
	}

	UFUNCTION() double GetCameraSpeed() { return GetCharacterSettings().CameraSpeed; }
	UFUNCTION() void SetCameraSpeed(const double Value) { GetCharacterSettings().CameraSpeed = Value; }

	UFUNCTION() bool GetIsColliding() { return GetCharacterSettings().bIsColliding; }
	UFUNCTION() void SetIsColliding(const bool bValue)
	{
		GetCharacterSettings().bIsColliding = bValue;
		OnUpdateProperties();
	}

public:
	UFUNCTION(BlueprintCallable)
	bool GetIsCurrentCharacter() const { return GetCharacterSettings().bIsCurrentCharacter; }

private:
	UFUNCTION() bool GetResetLocationAndRotation() { return GetCharacterSettings().bResetLocationAndRotation; }
	UFUNCTION() void SetResetLocationAndRotation(const bool bValue) { GetCharacterSettings().bResetLocationAndRotation = bValue; }

// FUNCTIONS
public:
	UFUNCTION(BlueprintCallable)
	void Init(UCharactersManager* InManager);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SelectAsCurrent();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeselect();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPropertiesConstructData* GetProperties();

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateProperties();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetStartLocationAndRotation();
	
};
