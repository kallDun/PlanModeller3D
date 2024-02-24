// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "InstrumentsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInstrumentManagerAction);

class UCharactersManager;
class APMCharacter;
class UInstrumentsManagerData;
class ACharacterInstrument;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UInstrumentsManager : public UObject, public IInitializable
{
	GENERATED_BODY()
	UInstrumentsManager() = default;

protected:
	UPROPERTY()
	UInstrumentsManagerData* Data;

	UPROPERTY()
	UCharactersManager* CharactersManager;
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<ACharacterInstrument*> Instruments = {};
	
	UPROPERTY(BlueprintReadOnly)
	ACharacterInstrument* ActiveInstrument;

	UPROPERTY(BlueprintAssignable)
	FInstrumentManagerAction OnInstrumentActivated;

	UPROPERTY(BlueprintAssignable)
	FInstrumentManagerAction OnInstrumentDeactivated;

public:
	virtual void Init_Implementation(UPrimaryDataAsset* DataAsset) override;
	
	UFUNCTION(BlueprintCallable)
	ACharacterInstrument* ActivateInstrument(const FString& InstrumentName);
	
	UFUNCTION(BlueprintCallable)
	void DeactivateCurrentInstrument();

	UFUNCTION(BlueprintCallable)
	ACharacterInstrument* GetInstrument(const FString& InstrumentName);

	UFUNCTION(BlueprintCallable)
	FString GetInstrumentName(TSubclassOf<ACharacterInstrument> InstrumentType);

private:
	UFUNCTION()
	void OnBeforeCharacterSelected(APMCharacter* Character);
};
