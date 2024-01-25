// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FurnitureControllerData.h"
#include "Models/SaveData/PlanModelType.h"
#include "Services/Initialization/Initializable.h"
#include "Services/Save/LoadedFromSave.h"
#include "Services/Shared/Enums/CrudActionType.h"
#include "UObject/Object.h"
#include "FurnitureController.generated.h"


struct FMFurniture;
class UPoolsSystem;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UFurnitureController : public UObject, public IInitializable, public ILoadedFromSave
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UFurnitureControllerData* Data;

	UPROPERTY()
	UPlanModellerSaveData* SaveData;

	UPROPERTY()
	UPoolsSystem* PoolsSystem;

	UPROPERTY()
	TMap<FString, AFurniture*> FurnituresMap = {};
	
public:
	virtual void Init_Implementation(UPrimaryDataAsset* DataAsset) override;
	
	virtual void LoadFromSave_Implementation(UPlanModellerSaveData* Save) override;

	virtual void BeginDestroy() override;
	
private:
	UFUNCTION()
	AFurniture* CreateFurniture(const FMFurniture& FurnitureModel, AActor* Parent, const FString& Id);

	UFUNCTION()
	void DestroyFurniture(AFurniture* Furniture);

	UFUNCTION()
	void OnModelChanged(ECrudActionType ActionType, EPlanModelType ModelType, FString ObjectId);	
};
