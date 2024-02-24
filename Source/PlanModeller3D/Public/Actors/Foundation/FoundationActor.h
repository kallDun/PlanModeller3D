// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "FoundationActor.generated.h"

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API AFoundationActor : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()

public:
	AFoundationActor() = default;

protected:	
	UFUNCTION()
	bool TryToSetMaterial(FName MaterialID, int Index) const;
	
};
