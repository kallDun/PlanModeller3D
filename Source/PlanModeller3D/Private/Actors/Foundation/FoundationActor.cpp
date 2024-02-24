// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foundation/FoundationActor.h"
#include "Core/CoreFunctionLib.h"
#include "Managers/Material/MaterialsManager.h"
#include "Widgets/Properties/PropertiesConstructData.h"


bool AFoundationActor::TryToSetMaterial(const FName MaterialID, const int Index) const
{
	UMaterialInterface* Material = UCoreFunctionLib::GetMaterialsManager(this)->GetMaterialInterface(MaterialID);
	GetDynamicMeshComponent()->SetMaterial(Index, Material);
	return Material != nullptr;
}

UPropertiesConstructData* AFoundationActor::GetProperties_Implementation()
{
	return NewObject<UPropertiesConstructData>();
}

