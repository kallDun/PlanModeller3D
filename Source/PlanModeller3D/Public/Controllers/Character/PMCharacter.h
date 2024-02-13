// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PMCharacter.generated.h"

class UPropertiesConstructData;

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API APMCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	APMCharacter() { }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input")
	class UInputMappingContext* PlayerInputMappingContext;
	
public:
	UPROPERTY(BlueprintReadOnly)
	class UCharactersManager* Manager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	FName CharacterName;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCurrentCharacter = false;

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
	
};
