// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerGameInstance.h"
#include "Level/LevelTransitionController.h"
#include "Save/SavingService.h"

void UPlanModellerGameInstance::Init()
{
	Super::Init();
	TransitionController = NewObject<ULevelTransitionController>(this, LevelTransitionControllerClass);
	SavingService = NewObject<USavingService>(this, USavingService::StaticClass());
	SavingService->Init(SlotsCount);
}
