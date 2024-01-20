// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelType.h"
#include "UObject/Object.h"
#include "LevelTransitionController.generated.h"

class ULevelTransitionData;
class UUserWidget;

UCLASS(BlueprintType)
class PLANMODELLER3D_API ULevelTransitionController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Init(ULevelTransitionData* InLevelTransitionData);
	
	UFUNCTION(BlueprintCallable)
	void LoadLevel(ELevelType LevelType);

	UFUNCTION(BlueprintCallable)
	void LoadStreamLevel(ELevelType LevelType);
	
private:
	UPROPERTY()
	ULevelTransitionData* Data;
	
	UPROPERTY()
	UUserWidget* LoadingScreen;

	UFUNCTION()
	void CreateLoadingScreen();

	UFUNCTION()
	void OnLevelLoaded();
};
