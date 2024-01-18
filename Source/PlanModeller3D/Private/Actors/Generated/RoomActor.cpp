// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Generated/RoomActor.h"
#include "Core/CoreFunctionLib.h"
#include "Save/SavingService.h"
#include "Save/Data/SaveGameData.h"


void ARoomActor::Init_Implementation(const FDMRoom Room)
{
	DMRoom = Room;
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
		const auto Save = SavingService->CurrentSaveGame;
		if (Save->Plan3D.Rooms.Contains(DMRoom.Id))
		{
			MRoom = Save->Plan3D.Rooms[DMRoom.Id];
		}
		else
		{
			MRoom = FMRoom();
			Save->Plan3D.Rooms.Add(DMRoom.Id, MRoom);
		}
	}
}
