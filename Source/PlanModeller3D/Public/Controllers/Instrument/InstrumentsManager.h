// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Character/PMCharacter.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "InstrumentsManager.generated.h"

class UCharactersManager;
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
