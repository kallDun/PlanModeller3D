// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Foundation/FoundationControllerData.h"
#include "Controllers/Furnitures/FurnitureControllerData.h"
#include "GameFramework/GameStateBase.h"
#include "PlanModellerState.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APlanModellerState : public AGameStateBase
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

	virtual void BeginPlay() override;
	
};
