// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerState.h"
#include "Controllers/Material/MaterialsManager.h"
#include "Controllers/Foundation/FoundationController.h"
#include "Controllers/Furnitures/FurnitureController.h"
#include "Controllers/Character/CharactersManager.h"
#include "Controllers/Instrument/InstrumentsManager.h"
#include "Services/Initialization/ServicesAbstractFactory.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Save/SavingService.h"


void APlanModellerState::LoadLevel_Implementation()
{
	Super::LoadLevel_Implementation();
	
	MaterialsManager = UServicesAbstractFactory::CreateService<UMaterialsManager>(this, MaterialsManagerData);
	FoundationController = UServicesAbstractFactory::CreateService<UFoundationController>(this, FoundationControllerData);
	FurnitureController = UServicesAbstractFactory::CreateService<UFurnitureController>(this, FurnitureControllerData);
	CharactersManager = UServicesAbstractFactory::CreateService<UCharactersManager>(this, CharactersManagerData);
	InstrumentsManager = UServicesAbstractFactory::CreateService<UInstrumentsManager>(this, InstrumentsManagerData);
	
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
		if (const auto Save = SavingService->CurrentSaveGame)
		{
			FoundationController->LoadFromSave_Implementation(Save);
			FurnitureController->LoadFromSave_Implementation(Save);
		}
	}
}
