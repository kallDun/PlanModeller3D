// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foundation/WallActor.h"
#include "Core/CoreFunctionLib.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Models/Material/SavedMaterialData.h"
#include "Services/Save/SavingService.h"
#include "Utils/Vector2DArray.h"
#include "Utils/Vector2D_MathLib.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void AWallActor::Init_Implementation(const FDMWall Wall)
{
	DMWall = Wall;
	SavingService = UCoreFunctionLib::GetSavingService(this);
	
	const auto Save = SavingService->CurrentSaveGame;
	if (Save->Plan3D.Walls.Contains(DMWall.Id))
	{
		MWall = Save->Plan3D.Walls[DMWall.Id];
	}
	else
	{
		MWall = FMWall();
		Save->Plan3D.Walls.Add(DMWall.Id, MWall);
	}
	for (auto Door : Save->Plan2D.Doors)
	{
		if (Door.WallId == DMWall.Id)
		{
			DMDoors.Add(Door);
		}
	}
	for (auto Window : Save->Plan2D.Windows)
	{
		if (Window.WallId == DMWall.Id)
		{
			DMWindows.Add(Window);
		}
	}
	for (auto Room : Save->Plan2D.Rooms)
	{
		if (DMWall.IsConnectedToRoom(Room))
		{
			DMRooms.Add(Room);
		}
	}
	
	InitMaterials();
}

void AWallActor::InitializeMaterialVerticesForRooms()
{
	for (int i = 0; i < DMRooms.Num(); ++i)
	{
		const int Index = i + 1 + DMDoors.Num() + DMWindows.Num();
		auto ConnectedPoints = DMWall.GetConnectedPoints(DMRooms[i]);
		InitMaterialForRoom(FVector2DArray(UVector2D_MathLib::GetSquareFromTwoPoints(
			ConnectedPoints[0], ConnectedPoints[1], 0.1f)), Index);
	}
}

void AWallActor::InitMaterials()
{
	MaterialsCount = DMDoors.Num() + DMWindows.Num() + DMRooms.Num() + 1;
	
	auto MaterialsSet = TArray<UMaterialInterface*>();
	for (int i = 0; i <= MaterialsCount; ++i)
	{
		MaterialsSet.Add(nullptr);
	}
	GetDynamicMeshComponent()->ConfigureMaterialSet(MaterialsSet);

	// SETUP DOORS MATERIAL
	for (int i = 0; i < DMDoors.Num(); ++i)
	{
		int Index = i + 1;
		auto Name = "Door " + FString::FromInt(i + 1) + " (" + DMDoors[i].Name + ")";
		if (FSavedMaterialData* Mat = MWall.Materials.FindByPredicate([Index](const FSavedMaterialData& Element) { return Element.Index == Index; }))
		{
			Mat->MaterialName = Name;
			if (!TryToSetMaterial(Mat->MaterialID, Index))
			{
				Mat->MaterialID = FName();
			}
		}
		else
		{
			MWall.Materials.Add(FSavedMaterialData(Name, Index, FName()));
			TryToSetMaterial(FName(), Index);
		}
	}

	// SETUP WINDOWS MATERIAL
	for (int i = 0; i < DMWindows.Num(); ++i)
	{
		int Index = i + 1 + DMDoors.Num();
		auto Name = "Window " + FString::FromInt(i + 1) + " (" + DMWindows[i].Name + ")";
		if (FSavedMaterialData* Mat = MWall.Materials.FindByPredicate([Index](const FSavedMaterialData& Element) { return Element.Index == Index; }))
		{
			Mat->MaterialName = Name;
			if (!TryToSetMaterial(Mat->MaterialID, Index))
			{
				Mat->MaterialID = FName();
			}
		}
		else
		{
			MWall.Materials.Add(FSavedMaterialData(Name, Index, FName()));
			TryToSetMaterial(FName(), Index);
		}
	}

	// SETUP ROOMS MATERIAL
	for (int i = 0; i < DMRooms.Num(); ++i)
	{
		int Index = i + 1 + DMDoors.Num() + DMWindows.Num();
		auto Name = "Room " + FString::FromInt(i + 1) + " (" + DMRooms[i].Name + ")";
		if (FSavedMaterialData* Mat = MWall.Materials.FindByPredicate([Index](const FSavedMaterialData& Element) { return Element.Index == Index; }))
		{
			Mat->MaterialName = Name;
			if (!TryToSetMaterial(Mat->MaterialID, Index))
			{
				Mat->MaterialID = FName();
			}
		}
		else
		{
			MWall.Materials.Add(FSavedMaterialData(Name, Index, FName()));
			TryToSetMaterial(FName(), Index);
		}
	}

	// SETUP WALL MATERIAL
	const auto WallName = "Base Material";
	if (FSavedMaterialData* Mat = MWall.Materials.FindByPredicate([this](const FSavedMaterialData& Element) { return Element.Index == MaterialsCount; }))
	{
		Mat->MaterialName = WallName;
		if (!TryToSetMaterial(Mat->MaterialID, MaterialsCount))
		{
			Mat->MaterialID = FName();
		}
	}
	else
	{
		MWall.Materials.Add(FSavedMaterialData(WallName, MaterialsCount, FName()));
		TryToSetMaterial(FName(), MaterialsCount);
	}

	SaveMWall();
}

UPropertiesConstructData* AWallActor::GetProperties_Implementation()
{
	UPropertiesConstructData* Properties = Super::GetProperties_Implementation();

	for (FSavedMaterialData MaterialData : MWall.Materials)
	{
		FOnGetMaterialValue GetMaterial = FOnGetMaterialValue();
		GetMaterial.BindDynamic(this, &AWallActor::GetMaterialValue);
		FOnSetMaterialValue SetMaterial = FOnSetMaterialValue();
		SetMaterial.BindDynamic(this, &AWallActor::SetMaterialValue);
		Properties->MaterialProperties.Add(FMaterialPropertyConstructObject(
			MaterialData.Index, FText::FromString(MaterialData.MaterialName),
			FText::FromString(GetActorName()),
			GetMaterial, SetMaterial, MaterialData.Index));
	}
	
	return Properties;
}

FString AWallActor::GetActorName() const
{
	return "Wall '" + DMWall.Name + "'";
}

FString AWallActor::GetClosestRoomID(const FVector Point) const
{
	FString ClosestRoomID;
	float MinDistance = TNumericLimits<float>::Max();
	for (const FDMRoom& Room : DMRooms)
	{
		const FVector2DArray RoomPoints = FVector2DArray(Room.Points);
		const FVector2D ClosestPoint = UVector2D_MathLib::GetClosestPointOnPolygon(RoomPoints, FVector2D(Point));
		const float Distance = FVector2D::Distance(FVector2D(Point), ClosestPoint);
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestRoomID = Room.Id;
		}
	}
	return ClosestRoomID;
}

// GETTERS & SETTERS

void AWallActor::SaveMWall()
{
	const auto Save = SavingService->CurrentSaveGame;
	Save->Plan3D.Walls[DMWall.Id] = MWall;
}

FName AWallActor::GetMaterialValue(const int Index)
{
	if (const FSavedMaterialData* Mat = MWall.Materials.FindByPredicate([Index](const FSavedMaterialData& Element)
	{
		return Element.Index == Index;
	}))
	{
		return Mat->MaterialID;
	}
	return FName();
}

void AWallActor::SetMaterialValue(const FName Value, const int Index)
{
	if (FSavedMaterialData* Mat = MWall.Materials.FindByPredicate([Index](const FSavedMaterialData& Element)
	{
		return Element.Index == Index;
	}))
	{
		TryToSetMaterial(Value, Index);
		Mat->MaterialID = Value;
		SaveMWall();
	}
}
