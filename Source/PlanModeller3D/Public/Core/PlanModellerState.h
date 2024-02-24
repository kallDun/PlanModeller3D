// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/Character/CharactersManagerData.h"
#include "Managers/Foundation/FoundationControllerData.h"
#include "Managers/Furnitures/FurnitureControllerData.h"
#include "Managers/Instrument/InstrumentsManagerData.h"
#include "Managers/Material/MaterialsManagerData.h"
#include "Services/Level/LevelLoadGameState.h"
#include "PlanModellerState.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APlanModellerState : public ALevelLoadGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "State")
	UMaterialsManagerData* MaterialsManagerData;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UMaterialsManager* MaterialsManager;
	
	UPROPERTY(EditDefaultsOnly, Category = "State")
	UFoundationControllerData* FoundationControllerData;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UFoundationController* FoundationController;

	UPROPERTY(EditDefaultsOnly, Category = "State")
	UFurnitureControllerData* FurnitureControllerData;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UFurnitureController* FurnitureController;

	UPROPERTY(EditDefaultsOnly, Category = "State")
	UCharactersManagerData* CharactersManagerData;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UCharactersManager* CharactersManager;

	UPROPERTY(EditDefaultsOnly, Category = "State")
	UInstrumentsManagerData* InstrumentsManagerData;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UInstrumentsManager* InstrumentsManager;

protected:
	virtual void LoadLevel_Implementation() override;
	
};
