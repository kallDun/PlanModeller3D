// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foundation/WallActor.h"
#include "Core/CoreFunctionLib.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Controllers/Material/SavedMaterialData.h"
#include "Services/Save/SavingService.h"


void AWallActor::Init_Implementation(const FDMWall Wall)
{
	DMWall = Wall;
	if (const auto SavingService = UCoreFunctionLib::GetSavingService(this))
	{
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
	}
	InitMaterials();
}

void AWallActor::InitMaterials()
{
	MaterialsCount = DMDoors.Num() + DMWindows.Num() + 1;
	
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
		}
	}

	// SETUP WALL MATERIAL
	const auto WallName = "Wall Material";
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
		TryToSetMaterial(Mat->MaterialID, MaterialsCount);
	}
}

bool AWallActor::TryToSetMaterial(FName MaterialID, const int Index) const
{
	UMaterialInterface* Material = nullptr;
	GetDynamicMeshComponent()->SetMaterial(Index, Material);
	return Material != nullptr;
}
