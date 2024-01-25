// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MFurniture.h"
#include "MDoor.h"
#include "MRoom.h"
#include "MWall.h"
#include "MWindow.h"
#include "Kismet/KismetStringLibrary.h"
#include "MPlan.generated.h"


UCLASS(BlueprintType)
class UMPlan : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMRoom> Rooms = {};

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMWall> Walls = {};

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMWindow> Windows = {};

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMDoor> Doors = {};
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMFurniture> Furnitures = {};

	UFUNCTION(BlueprintCallable)
	FString GetUniqueFurnitureID() const;
};

inline FString UMPlan::GetUniqueFurnitureID() const
{
	int MaxID = 0;
	for (auto Furniture : Furnitures)
	{
		const int ID = UKismetStringLibrary::Conv_StringToInt(Furniture.Key);
		if (ID > MaxID)
		{
			MaxID = ID;
		}
	}
	return FString::FromInt(MaxID + 1);
}
