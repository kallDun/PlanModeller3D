// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Models/Instrument/InstrumentType.h"
#include "CharacterInstrument.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInstrumentAction);

class APMCharacter;
class UInstrumentsManager;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API ACharacterInstrument : public AActor
{
	GENERATED_BODY()

public:
	ACharacterInstrument() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Instrument State")
	FString InstrumentName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instrument State")
	EInstrumentType InstrumentType;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	UInstrumentsManager* Manager;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	APMCharacter* Character;
	
	UPROPERTY(BlueprintAssignable, Category = "Instrument State")
	FInstrumentAction OnInstrumentUsed;

	UPROPERTY(BlueprintAssignable, Category = "Instrument State")
	FInstrumentAction OnInstrumentDeactivated;

	UFUNCTION()
	void Init(UInstrumentsManager* InstrumentsManager);

	UFUNCTION()
	virtual void Activate(APMCharacter* InCharacter);

	UFUNCTION()
	virtual void Deactivate();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeactivated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Preview();
};
