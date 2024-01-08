// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerGameInstance.h"
#include "Level/LevelTransitionController.h"

void UPlanModellerGameInstance::Init()
{
	Super::Init();
	TransitionController = NewObject<ULevelTransitionController>(this, LevelTransitionControllerClass);
}
