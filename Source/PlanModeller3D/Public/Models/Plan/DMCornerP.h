// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DMCornerP.generated.h"

USTRUCT()
struct FDMCornerP
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	bool Enable;

	UPROPERTY()
	bool Visible;
};
