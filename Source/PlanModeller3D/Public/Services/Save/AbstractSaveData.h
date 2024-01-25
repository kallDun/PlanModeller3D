// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/Object.h"
#include "AbstractSaveData.generated.h"

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API UAbstractSaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveName;
	
	UFUNCTION()
	virtual void Init(const FString& Name)
	{
		SaveName = Name;
	}
};

