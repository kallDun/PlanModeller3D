// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Models/Material/StoredMaterialData.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "MaterialsManager.generated.h"

class UMaterialsManagerData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UMaterialsManager : public UObject, public IInitializable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UMaterialsManagerData* Data;

public:
	virtual void Init_Implementation(UPrimaryDataAsset* DataAsset) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FStoredMaterialData> GetMaterials() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UMaterialInterface* GetMaterial(FName MaterialID) const;
	
};
