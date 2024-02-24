// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Initialization/Initializable.h"
#include "Services/Save/LoadedFromSave.h"
#include "UObject/Object.h"
#include "FoundationController.generated.h"

class AWallActor;
class ARoomActor;
class UFoundationControllerData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UFoundationController : public UObject, public IInitializable, public ILoadedFromSave
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UFoundationControllerData* Data;

	UPROPERTY(BlueprintReadOnly)
	TArray<ARoomActor*> RoomActors;

	UPROPERTY(BlueprintReadOnly)
	TArray<AWallActor*> WallActors;

	virtual void Init_Implementation(UPrimaryDataAsset* DataAsset) override;

	virtual void LoadFromSave_Implementation(UPlanModellerSaveData* Save) override;
};
