// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FoundationControllerData.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UFoundationControllerData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ARoomActor> RoomActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AWallActor> WallActorClass;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("FoundationControllerData", GetFName());
	}
};
