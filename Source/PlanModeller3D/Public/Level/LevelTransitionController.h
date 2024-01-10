// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelType.h"
#include "UObject/Object.h"
#include "LevelTransitionController.generated.h"

class UUserWidget;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API ULevelTransitionController : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<ELevelType, FName> LevelPaths;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoadingScreenClass;

	UFUNCTION(BlueprintCallable)
	void LoadLevel(ELevelType LevelType);

	UFUNCTION(BlueprintCallable)
	void LoadStreamLevel(ELevelType LevelType);
	
private:
	UPROPERTY()
	UUserWidget* LoadingScreen;

	UFUNCTION()
	void CreateLoadingScreen();

	UFUNCTION()
	void OnLevelLoaded();
};
