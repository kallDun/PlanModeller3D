// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CoreFunctionLib.h"
#include "Core/MenuGameMode.h"
#include "Core/PlanModellerGameInstance.h"
#include "Core/PlanModellerGameMode.h"
#include "Core/PlanModellerState.h"

UPlanModellerGameInstance* UCoreFunctionLib::GetPMInstance(const UObject* WorldContextObject)
{	
	return Cast<UPlanModellerGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());
}

APlanModellerGameMode* UCoreFunctionLib::GetPMGameMode(const UObject* WorldContextObject)
{
	return Cast<APlanModellerGameMode>(WorldContextObject->GetWorld()->GetAuthGameMode());
}

AMenuGameMode* UCoreFunctionLib::GetMenuGameMode(const UObject* WorldContextObject)
{
	return Cast<AMenuGameMode>(WorldContextObject->GetWorld()->GetAuthGameMode());
}

APlanModellerState* UCoreFunctionLib::GetPMState(const UObject* WorldContextObject)
{
	return Cast<APlanModellerState>(WorldContextObject->GetWorld()->GetGameState());
}

// SERVICES

USavingService* UCoreFunctionLib::GetSavingService(const UObject* WorldContextObject)
{
	return GetPMInstance(WorldContextObject)->SavingService;
}

ULevelTransitionController* UCoreFunctionLib::GetTransitionController(const UObject* WorldContextObject)
{
	return GetPMInstance(WorldContextObject)->TransitionController;
}

UPoolsSystem* UCoreFunctionLib::GetPoolsSystem(const UObject* WorldContextObject)
{
	return GetPMInstance(WorldContextObject)->PoolsSystem;
}

UManagerUI* UCoreFunctionLib::GetManagerUI(const UObject* WorldContextObject)
{
	return GetPMInstance(WorldContextObject)->ManagerUI;
}

// CONTROLLERS

UMaterialsManager* UCoreFunctionLib::GetMaterialsManager(const UObject* WorldContextObject)
{
	return GetPMState(WorldContextObject)->MaterialsManager;
}

UFoundationController* UCoreFunctionLib::GetFoundationController(const UObject* WorldContextObject)
{
	return GetPMState(WorldContextObject)->FoundationController;
}

UFurnitureController* UCoreFunctionLib::GetFurnitureController(const UObject* WorldContextObject)
{
	return GetPMState(WorldContextObject)->FurnitureController;
}

UCharactersManager* UCoreFunctionLib::GetCharactersManager(const UObject* WorldContextObject)
{
	return GetPMState(WorldContextObject)->CharactersManager;
}

UInstrumentsManager* UCoreFunctionLib::GetInstrumentsManager(const UObject* WorldContextObject)
{
	return GetPMState(WorldContextObject)->InstrumentsManager;
}

UFurnitureGenerationController* UCoreFunctionLib::GetFurnitureGenerationController(const UObject* WorldContextObject)
{
	return GetPMState(WorldContextObject)->FurnitureGenerationController;
}

