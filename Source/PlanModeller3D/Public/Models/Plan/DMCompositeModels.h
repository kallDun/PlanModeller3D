#pragma once

#include "DMRoom.h"
#include "DMWall.h"
#include "DMDoorWindow.h"
#include "DMCornerP.h"
#include "DMCompositeModels.generated.h"

USTRUCT(BlueprintType)
struct FDMCompositeModels
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FDMRoom> Rooms;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FDMWall> Walls;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FDMDoorWindow> Doors;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FDMDoorWindow> Windows;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FDMCornerP> Corners;
};
