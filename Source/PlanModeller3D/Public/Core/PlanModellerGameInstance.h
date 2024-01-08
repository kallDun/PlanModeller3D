// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlanModellerGameInstance.generated.h"

class ULevelTransitionController;

UCLASS(Blueprintable, BlueprintType)
class PLANMODELLER3D_API UPlanModellerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	__override virtual void Init() override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	ULevelTransitionController* TransitionController;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TSubclassOf<ULevelTransitionController> LevelTransitionControllerClass;

};
