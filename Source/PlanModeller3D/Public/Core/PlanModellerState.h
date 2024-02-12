// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Character/CharactersManager.h"
#include "Controllers/Character/CharactersManagerData.h"
#include "Controllers/Foundation/FoundationControllerData.h"
#include "Controllers/Furnitures/FurnitureControllerData.h"
#include "Services/Level/LevelLoadGameState.h"
#include "PlanModellerState.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APlanModellerState : public ALevelLoadGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Foundation")
	UFoundationControllerData* FoundationControllerData;

	UPROPERTY(BlueprintReadOnly, Category = "Foundation")
	class UFoundationController* FoundationController;

	UPROPERTY(EditDefaultsOnly, Category = "Furniture")
	UFurnitureControllerData* FurnitureControllerData;

	UPROPERTY(BlueprintReadOnly, Category = "Furniture")
	class UFurnitureController* FurnitureController;

	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	UCharactersManagerData* CharactersManagerData;

	UPROPERTY(BlueprintReadOnly, Category = "Characters")
	UCharactersManager* CharactersManager;

protected:
	virtual void LoadLevel_Implementation() override;
	
};
