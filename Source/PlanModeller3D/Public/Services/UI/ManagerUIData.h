// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PanelUIData.h"
#include "UObject/Object.h"
#include "ManagerUIData.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UManagerUIData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPanelUIData> Panels;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ManagerUIData", GetFName());
	}
};
