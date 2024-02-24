// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Material/MaterialsManager.h"
#include "Controllers/Material/MaterialsManagerData.h"


void UMaterialsManager::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UMaterialsManagerData>(DataAsset);
}

TArray<FStoredMaterialData> UMaterialsManager::GetMaterials() const
{
	return Data->Materials;
}

UMaterialInterface* UMaterialsManager::GetMaterial(const FName MaterialID) const
{
	for (auto Mat : GetMaterials())
	{
		if (Mat.ID == MaterialID)
		{
			return Mat.Interface;
		}
	}
	return nullptr;
}
