// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharactersManagerData.generated.h"

class APMCharacter;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UCharactersManagerData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<APMCharacter>> CharacterClasses;

	__override virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("CharactersManagerData", GetFName());
	}
};
