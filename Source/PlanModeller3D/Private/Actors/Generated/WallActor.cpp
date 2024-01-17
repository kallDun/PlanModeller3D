// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Generated/WallActor.h"
#include "Core/CoreFunctionLib.h"
#include "Save/SavingService.h"
#include "Save/Data/SaveGameData.h"


AWallActor::AWallActor()
{
	
}

void AWallActor::Init(const FDMWall Wall)
{
	DMWall = Wall;
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
		if (const auto Save = SavingService->CurrentSaveGame;
			Save->Plan3D.Walls.Contains(DMWall.Id))
		{
			MWall = Save->Plan3D.Walls[DMWall.Id];
		}
		else
		{
			MWall = FMWall();
			Save->Plan3D.Walls.Add(DMWall.Id, MWall);
		}
	}
}

