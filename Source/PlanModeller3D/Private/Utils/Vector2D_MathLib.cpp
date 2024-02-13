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
