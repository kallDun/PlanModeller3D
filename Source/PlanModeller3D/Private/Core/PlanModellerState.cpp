// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlanModellerState.h"
#include "Actors/Generated/RoomActor.h"
#include "Actors/Generated/WallActor.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Save/SavingService.h"
#include "Services/Save/Data/SaveGameData.h"


void APlanModellerState::BeginPlay()
{
	Super::BeginPlay();
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
		const auto Save = SavingService->CurrentSaveGame;
		for (const auto RoomDto : Save->Plan2D.Rooms)
		{
			auto Room = GetWorld()->SpawnActor<ARoomActor>(RoomActorClass);
			Room->Init(RoomDto);
			RoomActors.Add(Room);
		}
		for (const auto WallDto : Save->Plan2D.Walls)
		{
			auto Wall = GetWorld()->SpawnActor<AWallActor>(WallActorClass);
			Wall->Init(WallDto);
			WallActors.Add(Wall);
		}
	}
}
