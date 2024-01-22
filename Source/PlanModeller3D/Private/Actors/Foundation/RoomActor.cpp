// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foundation/RoomActor.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Save/SavingService.h"
#include "Services/Save/Data/SaveGameData.h"


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
