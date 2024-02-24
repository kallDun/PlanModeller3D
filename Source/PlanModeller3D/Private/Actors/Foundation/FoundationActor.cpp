// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Foundation/FoundationActor.h"
#include "Controllers/Material/MaterialsManager.h"
#include "Core/CoreFunctionLib.h"


bool AFoundationActor::TryToSetMaterial(const FName MaterialID, const int Index) const
{
	UMaterialInterface* Material = UCoreFunctionLib::GetMaterialsManager(this)->GetMaterial(MaterialID);
	GetDynamicMeshComponent()->SetMaterial(Index, Material);
	return Material != nullptr;
}
