// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "Models/Plan/DMWall.h"
#include "Models/Plan3D/MWall.h"
#include "WallActor.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API AWallActor : public AGeneratedDynamicMeshActor 
{
	GENERATED_BODY()

public:
	AWallActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDMWall	DMWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMWall MWall;

	UFUNCTION(BlueprintCallable)
	void Init(FDMWall Wall);

};
