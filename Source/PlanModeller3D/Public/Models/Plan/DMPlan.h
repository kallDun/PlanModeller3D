// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DMCornerP.h"
#include "DMDoorWindow.h"
#include "DMParametricItem.h"
#include "DMRoom.h"
#include "DMWall.h"
#include "DMPlan.generated.h"

USTRUCT(BlueprintType)
struct FDMPlan
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
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FDMParametricItem> ParametricItems;
};
