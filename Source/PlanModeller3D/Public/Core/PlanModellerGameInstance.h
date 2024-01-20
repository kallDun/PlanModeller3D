// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlanModellerGameInstance.generated.h"

class USavingServiceData;
class ULevelTransitionData;
class UPoolsSystem;
class UPoolSystemData;
class USavingService;
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
	ULevelTransitionData* LevelTransitionData;

	UPROPERTY(BlueprintReadOnly, Category = "SaveGame")
	USavingService* SavingService;
	
	UPROPERTY(EditDefaultsOnly, Category = "SaveGame")
	USavingServiceData* SavingServiceData;

	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	UPoolsSystem* PoolsSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pool System")
	UPoolSystemData* PoolsData;
};
