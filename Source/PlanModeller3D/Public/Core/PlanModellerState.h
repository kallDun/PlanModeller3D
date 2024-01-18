// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlanModellerState.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API APlanModellerState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARoomActor> RoomActorClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWallActor> WallActorClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<ARoomActor*> RoomActors;

	UPROPERTY(BlueprintReadOnly)
	TArray<AWallActor*> WallActors;

	virtual void BeginPlay() override;
	
};
