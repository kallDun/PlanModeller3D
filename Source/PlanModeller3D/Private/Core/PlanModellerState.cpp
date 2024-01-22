// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerState.h"
#include "Controllers/Foundation/FoundationController.h"
#include "Controllers/Furnitures/FurnitureController.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Initialization/ServicesAbstractFactory.h"
#include "Services/Save/SavingService.h"
#include "Services/Save/Data/SaveGameData.h"


void APlanModellerState::BeginPlay()
{
	Super::BeginPlay();

	FoundationController = UServicesAbstractFactory::CreateService<UFoundationController>(this, FoundationControllerData);
	FurnitureController = UServicesAbstractFactory::CreateService<UFurnitureController>(this, FurnitureControllerData);
	
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
		const auto Save = SavingService->CurrentSaveGame;
		FoundationController->LoadFromSave_Implementation(Save);
	}
}
