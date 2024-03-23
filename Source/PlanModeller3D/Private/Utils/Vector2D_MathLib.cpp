// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Vector2D_MathLib.h"
#include "Utils/Vector2DArray.h"


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

FVector2D UVector2D_MathLib::GetClosestPointOnPolygon(const FVector2DArray& Vector2Ds, const FVector2D Vector2)
{
	auto ClosestPoint = FVector2D(0, 0);
	auto MinDistance = TNumericLimits<float>::Max();
	for (auto& Point : Vector2Ds.Points)
	{
		const auto Distance = FVector2D::Distance(Point, Vector2);
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestPoint = Point;
		}
	}
	return ClosestPoint;
}

FVector2D UVector2D_MathLib::GetDirectionVectorFromWallToRoom(const FVector2DArray& WallPoints,
	const FVector2DArray& RoomPoints, UObject* WorldContextObject)
{
	// get first same point in both arrays
	auto SamePoint = FVector2D(0, 0);
	for (auto& WallPoint : WallPoints.Points)
	{
		for (auto& RoomPoint : RoomPoints.Points)
		{
			if (WallPoint.Equals(RoomPoint))
			{
				SamePoint = WallPoint;
				goto Next;
			}
		}
	}

Next:
	// Debug draw point
	/*DrawDebugPoint(WorldContextObject->GetWorld(), FVector(SamePoint, 300),
		10, FColor::Red, false, .5);*/
	
	// find closest point to SamePoint in WallPoints
	auto ClosestPoint = FVector2D(0, 0);
	auto MinDistance = TNumericLimits<float>::Max();
	for (auto& WallPoint : WallPoints.Points)
	{
		if (WallPoint.Equals(SamePoint)) continue;
		const auto Distance = FVector2D::Distance(WallPoint, SamePoint);
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestPoint = WallPoint;
		}
	}

	// Debug draw line
	/*DrawDebugLine(WorldContextObject->GetWorld(),
		FVector(ClosestPoint, 300), FVector(SamePoint, 300),
		FColor::Green, false, .5);*/
	
	// get direction vector from ClosestPoint to SamePoint
	return (SamePoint - ClosestPoint).GetSafeNormal();
}

FRotator UVector2D_MathLib::GetRotationFromDirectionVector(const FVector2D& DirectionVector)
{
	FRotator Rotation = FRotator(0, 0, 0);
	Rotation.Yaw = FMath::RadiansToDegrees(FMath::Atan2(DirectionVector.Y, DirectionVector.X));
	return Rotation;
}
