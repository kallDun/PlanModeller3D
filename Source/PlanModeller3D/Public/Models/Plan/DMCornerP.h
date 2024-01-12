// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DMCornerP.generated.h"

USTRUCT(BlueprintType)
struct FDMCornerP
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString Id;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Position;

	UPROPERTY(BlueprintReadWrite)
	bool Enable;

	UPROPERTY(BlueprintReadWrite)
	bool Visible;
};
