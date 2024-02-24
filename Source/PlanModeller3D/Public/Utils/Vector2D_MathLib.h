// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Vector2D_MathLib.generated.h"

UCLASS()
class PLANMODELLER3D_API UVector2D_MathLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static FVector2D GetCenter(const TArray<FVector2D>& Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static TArray<FVector2D> GetSquareFromTwoPoints(const FVector2D& Point1, const FVector2D& Point2, const float Thickness);
	
};
