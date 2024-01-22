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

	UPROPERTY(BlueprintReadOnly, Category = "Save Game")
	USavingService* SavingService;
	
	UPROPERTY(EditDefaultsOnly, Category = "Save Game")
	USavingServiceData* SavingServiceData;

	UPROPERTY(BlueprintReadOnly, Category = "Pools System")
	UPoolsSystem* PoolsSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pools System")
	UPoolSystemData* PoolsData;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UManagerUI* ManagerUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	class UManagerUIData* ManagerUIData;
};
