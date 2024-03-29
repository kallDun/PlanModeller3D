// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Foundation/FoundationController.h"
#include "Actors/Foundation/RoomActor.h"
#include "Actors/Foundation/WallActor.h"
#include "Managers/Foundation/FoundationControllerData.h"
#include "Models/SaveData/PlanModellerSaveData.h"


void UFoundationController::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UFoundationControllerData>(DataAsset);
}

void UFoundationController::LoadFromSave_Implementation(UPlanModellerSaveData* Save)
{
	ILoadedFromSave::LoadFromSave_Implementation(Save);
	for (const auto RoomDto : Save->Plan2D.Rooms)
	{
		auto Room = GetWorld()->SpawnActor<ARoomActor>(Data->RoomActorClass);
		Room->Init(RoomDto);
		RoomActors.Add(Room);
		FoundationActors.Add(Room);
	}
	for (const auto WallDto : Save->Plan2D.Walls)
	{
		auto Wall = GetWorld()->SpawnActor<AWallActor>(Data->WallActorClass);
		Wall->Init(WallDto);
		WallActors.Add(Wall);
		FoundationActors.Add(Wall);
	}
}

AActor* UFoundationController::GetRoomById(const FString& Id)
{
	if (const auto RoomLink = RoomActors.FindByPredicate([Id](const auto Room) { return Room->DMRoom.Id == Id; }))
	{
		return *RoomLink;
	}
	return nullptr;
}

AActor* UFoundationController::GetWallById(const FString& Id)
{
	if (const auto WallLink = WallActors.FindByPredicate([Id](const auto Wall) { return Wall->DMWall.Id == Id; }))
	{
		return *WallLink;
	}
	return nullptr;
}
