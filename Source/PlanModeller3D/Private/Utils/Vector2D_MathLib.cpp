// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Vector2D_MathLib.h"

FVector2D UVector2D_MathLib::GetCenter(const TArray<FVector2D>& Points)
{
	FVector2D Center = FVector2D(0, 0);
	for (auto& Point : Points)
	{
		Center += Point;
	}
	Center /= Points.Num();
	return Center;
}

TArray<FVector2D> UVector2D_MathLib::GetSquareFromTwoPoints(const FVector2D& Point1, const FVector2D& Point2,
	const float Thickness)
{
	TArray<FVector2D> Square = TArray<FVector2D>();
	const FVector2D Direction = (Point2 - Point1).GetSafeNormal();
	const FVector2D Normal = FVector2D(Direction.Y, -Direction.X);
	Square.Add(Point1 + Normal * Thickness);
	Square.Add(Point2 + Normal * Thickness);
	Square.Add(Point2 - Normal * Thickness);
	Square.Add(Point1 - Normal * Thickness);
	return Square;
}
