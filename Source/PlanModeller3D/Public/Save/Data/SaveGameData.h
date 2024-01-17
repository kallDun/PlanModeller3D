// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Models/Plan/DMPlan.h"
#include "Models/Plan3D/MPlan.h"
#include "UObject/Object.h"
#include "SaveGameData.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PLANMODELLER3D_API USaveGameData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDMPlan Plan2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMPlan Plan3D;
};
