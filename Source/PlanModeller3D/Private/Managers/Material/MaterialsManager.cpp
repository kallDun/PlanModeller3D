// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Material/MaterialsManager.h"
#include "Managers/Material/MaterialsManagerData.h"


void UMaterialsManager::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UMaterialsManagerData>(DataAsset);
}

TArray<FStoredMaterialData> UMaterialsManager::GetMaterials() const
{
	return Data->Materials;
}

FStoredMaterialData UMaterialsManager::GetMaterialData(FName MaterialID) const
{
	for (auto Mat : GetMaterials())
	{
		if (Mat.ID == MaterialID)
		{
			return Mat;
		}
	}
	return FStoredMaterialData();
}

UMaterialInterface* UMaterialsManager::GetMaterialInterface(const FName MaterialID) const
{
	return GetMaterialData(MaterialID).Interface;
}
