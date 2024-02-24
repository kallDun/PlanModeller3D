// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoundationActor.h"
#include "GameFramework/Actor.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "Models/Plan/DMRoom.h"
#include "Models/Plan3D/MRoom.h"
#include "RoomActor.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API ARoomActor : public AFoundationActor 
{
	GENERATED_BODY()

public:
	ARoomActor() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDMRoom	DMRoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMRoom MRoom;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(FDMRoom Room);
};
