// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InstrumentsManagerData.generated.h"

class ACharacterInstrument;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UInstrumentsManagerData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ACharacterInstrument>> InstrumentClasses;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("InstrumentsManagerData", GetFName());
	}
};
