// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FurnitureControllerData.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "FurnitureController.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UFurnitureController : public UObject, public IInitializable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UFurnitureControllerData* Data;

	virtual void Init_Implementation(UPrimaryDataAsset* DataAsset) override;
	
};
