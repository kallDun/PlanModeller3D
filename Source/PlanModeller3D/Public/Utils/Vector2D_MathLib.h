// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Vector2D_MathLib.generated.h"

struct FVector2DArray;

UCLASS()
class PLANMODELLER3D_API UVector2D_MathLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static FVector2D GetCenter(const TArray<FVector2D>& Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static TArray<FVector2D> GetSquareFromTwoPoints(const FVector2D& Point1, const FVector2D& Point2, const float Thickness);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static FVector2D GetClosestPointOnPolygon(const FVector2DArray& Vector2Ds, FVector2D Vector2);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static FVector2D GetDirectionVectorFromWallToRoom(const FVector2DArray& WallPoints, const FVector2DArray& RoomPoints, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core")
	static FRotator GetRotationFromDirectionVector(const FVector2D& DirectionVector);
};
