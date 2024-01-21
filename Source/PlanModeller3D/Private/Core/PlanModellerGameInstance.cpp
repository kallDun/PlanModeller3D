// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerGameInstance.h"
#include "Services/Level/LevelTransitionController.h"
#include "Services/Save/SavingService.h"
#include "Services/Pool/PoolsSystem.h"
#include "Services/UI/ManagerUI.h"

void UPlanModellerGameInstance::Init()
{
	Super::Init();
	
	TransitionController = NewObject<ULevelTransitionController>(this, ULevelTransitionController::StaticClass());
	TransitionController->Init(LevelTransitionData);
	
	SavingService = NewObject<USavingService>(this, USavingService::StaticClass());
	SavingService->Init(SavingServiceData);
	
	PoolsSystem = NewObject<UPoolsSystem>(this, UPoolsSystem::StaticClass());
	PoolsSystem->Init(PoolsData);

	ManagerUI = NewObject<UManagerUI>(this, UManagerUI::StaticClass());
	ManagerUI->Init(ManagerUIData);
}
