#pragma once

#include "DMRoom.h"
#include "DMWall.h"
#include "DMDoorWindow.h"
#include "DMCornerP.h"
#include "DMCompositeModels.generated.h"

USTRUCT()
struct FDMCompositeModels
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FDMRoom> Rooms;
	
	UPROPERTY()
	TArray<FDMWall> Walls;
	
	UPROPERTY()
	TArray<FDMDoorWindow> Doors;
	
	UPROPERTY()
	TArray<FDMDoorWindow> Windows;
	
	UPROPERTY()
	TArray<FDMCornerP> Corners;
};
