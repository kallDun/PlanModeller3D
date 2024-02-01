// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelType.h"
#include "GameFramework/GameStateBase.h"
#include "LevelLoadGameState.generated.h"

class ULevelTransitionController;

UCLASS(BlueprintType, Blueprintable)
class PLANMODELLER3D_API ALevelLoadGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ELevelType LevelType;

protected:
	UPROPERTY()
	ULevelTransitionController* TransitionController;

	UFUNCTION(BlueprintNativeEvent)
	void LoadLevel();
	
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
