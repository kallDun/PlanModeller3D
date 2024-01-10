// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DMCornerP.h"
#include "DMDoorWindow.h"
#include "DMParametricItem.h"
#include "DMRoom.h"
#include "DMWall.h"
#include "DMPlan.generated.h"

USTRUCT()
struct FDMPlan
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
	
	UPROPERTY()
	TArray<FDMParametricItem> ParametricItems;
};
