// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Instrument/SelectionConverterLib.h"
#include "Actors/Foundation/RoomActor.h"
#include "Actors/Foundation/WallActor.h"
#include "Actors/Furnitures/Furniture.h"
#include "Core/CoreFunctionLib.h"
#include "Managers/Foundation/FoundationController.h"
#include "Managers/Furnitures/FurnitureController.h"


FSceneObjectSelection USelectionConverterLib::ConvertToSelectionFromActor(AActor* Actor, uint8 AvailableSelections)
{
	if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
				EInstrumentAvailableSelection::IAS_Room))
	{
		if (const auto Room = Cast<ARoomActor>(Actor))
		{
			return FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Room,
				Room->DMRoom.Id, Room->DMRoom.Name);
		}
	}
	if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
		EInstrumentAvailableSelection::IAS_Wall))
	{
		if (const auto Wall = Cast<AWallActor>(Actor))
		{
			return FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Wall,
				Wall->DMWall.Id, Wall->DMWall.Name);
		}
	}
	if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
		EInstrumentAvailableSelection::IAS_Furniture))
	{
		if (const auto Furniture = Cast<AFurniture>(Actor))
		{
			return FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Furniture,
				Furniture->ID, Furniture->Data.Name);
		}
	}
	// else if TODO: add check for prop

	return FSceneObjectSelection();
}

AActor* USelectionConverterLib::ConvertToActorFromSelection(const UObject* WorldContextObject, const FSceneObjectSelection Selection)
{
	if (Selection.SelectionType == EInstrumentAvailableSelection::IAS_Room
		|| Selection.SelectionType == EInstrumentAvailableSelection::IAS_Wall)
	{
		if (const auto FoundationController = UCoreFunctionLib::GetFoundationController(WorldContextObject))
		{
			if (Selection.SelectionType == EInstrumentAvailableSelection::IAS_Room)
			{
				return FoundationController->GetRoomById(Selection.SelectionId);
			}
			if (Selection.SelectionType == EInstrumentAvailableSelection::IAS_Wall)
			{
				return FoundationController->GetWallById(Selection.SelectionId);
			}
		}
	}
	if (Selection.SelectionType == EInstrumentAvailableSelection::IAS_Furniture)
	{
		if (const auto FurnitureController = UCoreFunctionLib::GetFurnitureController(WorldContextObject))
		{
			return FurnitureController->GetFurnitureByID(Selection.SelectionId);
		}
	}
	// if TODO: add check for prop
	return nullptr;
}
