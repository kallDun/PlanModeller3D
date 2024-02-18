// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstrumentsManager.h"
#include "GameFramework/Actor.h"
#include "CharacterInstrument.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInstrumentAction);

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API ACharacterInstrument : public AActor
{
	GENERATED_BODY()

public:
	ACharacterInstrument() = default;

	UPROPERTY(EditDefaultsOnly, Category = "Instrument State")
	FString InstrumentName;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	UInstrumentsManager* Manager;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	APMCharacter* Character;
	
	UPROPERTY(BlueprintAssignable, Category = "Instrument State")
	FInstrumentAction OnInstrumentCalled;

	UFUNCTION()
	void Init(UInstrumentsManager* InstrumentsManager);

	UFUNCTION()
	void Activate(APMCharacter* InCharacter);

	UFUNCTION()
	void Deactivate();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeactivated();
};
