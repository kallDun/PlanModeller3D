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
