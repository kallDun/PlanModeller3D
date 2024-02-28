// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foundation/RoomActor.h"
#include "Core/CoreFunctionLib.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Services/Save/SavingService.h"
#include "Widgets/Properties/MaterialPropertyConstructObject.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void ARoomActor::Init_Implementation(const FDMRoom Room)
{
	DMRoom = Room;
	SavingService = UCoreFunctionLib::GetSavingService(this);
	
	if (SavingService)
	{
		const auto Save = SavingService->CurrentSaveGame;
		if (Save->Plan3D.Rooms.Contains(DMRoom.Id))
		{
			MRoom = Save->Plan3D.Rooms[DMRoom.Id];
		}
		else
		{
			MRoom = FMRoom();
			Save->Plan3D.Rooms.Add(DMRoom.Id, MRoom);
		}
	}
	InitMaterial();
}

UPropertiesConstructData* ARoomActor::GetProperties_Implementation()
{
	UPropertiesConstructData* Properties = Super::GetProperties_Implementation();

	// SETUP BASE MATERIAL PROPERTY
	FOnGetMaterialValue GetMaterial = FOnGetMaterialValue();
	GetMaterial.BindDynamic(this, &ARoomActor::GetMaterialValue);
	FOnSetMaterialValue SetMaterial = FOnSetMaterialValue();
	SetMaterial.BindDynamic(this, &ARoomActor::SetMaterialValue);
	Properties->MaterialProperties.Add(FMaterialPropertyConstructObject(
		MRoom.Material.Index, FText::FromString(MRoom.Material.MaterialName),
		FText::FromString(GetActorName()),
		GetMaterial, SetMaterial, MRoom.Material.Index));
	
	return Properties;
}

FString ARoomActor::GetActorName() const
{
	return "Room '" + DMRoom.Name + "'";
}

void ARoomActor::InitMaterial()
{
	auto MaterialsSet = TArray<UMaterialInterface*>();
	MaterialsSet.Add(nullptr);
	GetDynamicMeshComponent()->ConfigureMaterialSet(MaterialsSet);

	// SETUP BASE MATERIAL
	const auto WallName = "Base Material";
	if (MRoom.Material.MaterialName != FName())
	{
		MRoom.Material.MaterialName = WallName;
		if (!TryToSetMaterial(MRoom.Material.MaterialID, MRoom.Material.Index))
		{
			MRoom.Material.MaterialID = FName();
		}
	}
	else
	{
		MRoom.Material = FSavedMaterialData(WallName, 0, FName());
		TryToSetMaterial(FName(), MRoom.Material.Index);
	}
}

void ARoomActor::SaveMRoom() const
{
	const auto Save = SavingService->CurrentSaveGame;
	Save->Plan3D.Rooms[DMRoom.Id] = MRoom;
}

FName ARoomActor::GetMaterialValue(const int Index)
{
	return MRoom.Material.MaterialID;
}

void ARoomActor::SetMaterialValue(const FName Value, const int Index)
{
	TryToSetMaterial(Value, Index);
	MRoom.Material.MaterialID = Value;
	SaveMRoom();
}
