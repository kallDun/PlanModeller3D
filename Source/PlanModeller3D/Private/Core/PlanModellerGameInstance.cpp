// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerGameInstance.h"
#include "Services/Initialization/ServicesAbstractFactory.h"
#include "Services/Level/LevelTransitionController.h"
#include "Services/Level/LevelTransitionData.h"
#include "Services/Save/SavingService.h"
#include "Services/Pool/PoolsSystem.h"
#include "Services/Pool/PoolSystemData.h"
#include "Services/Save/SavingServiceData.h"
#include "Services/UI/ManagerUI.h"
#include "Services/UI/ManagerUIData.h"

void UPlanModellerGameInstance::Init()
{
	Super::Init();
	TransitionController = UServicesAbstractFactory::CreateService<ULevelTransitionController>(this, LevelTransitionData);
	SavingService = UServicesAbstractFactory::CreateService<USavingService>(this, SavingServiceData);
	PoolsSystem = UServicesAbstractFactory::CreateService<UPoolsSystem>(this, PoolsData);
	ManagerUI = UServicesAbstractFactory::CreateService<UManagerUI>(this, ManagerUIData);
}
