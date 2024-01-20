// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Generated/WallActor.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Save/SavingService.h"
#include "Services/Save/Data/SaveGameData.h"


void AWallActor::Init_Implementation(const FDMWall Wall)
{
	DMWall = Wall;
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
		const auto Save = SavingService->CurrentSaveGame;
		if (Save->Plan3D.Walls.Contains(DMWall.Id))
		{
			MWall = Save->Plan3D.Walls[DMWall.Id];
		}
		else
		{
			MWall = FMWall();
			Save->Plan3D.Walls.Add(DMWall.Id, MWall);
		}
		for (auto Door : Save->Plan2D.Doors)
		{
			if (Door.WallId == DMWall.Id)
			{
				DMDoors.Add(Door);
			}
		}
		for (auto Window : Save->Plan2D.Windows)
		{
			if (Window.WallId == DMWall.Id)
			{
				DMWindows.Add(Window);
			}
		}
	}
}

