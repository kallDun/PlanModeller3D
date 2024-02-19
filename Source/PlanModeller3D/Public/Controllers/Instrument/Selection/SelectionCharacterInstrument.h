// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneObjectSelection.h"
#include "Controllers/Instrument/CharacterInstrument.h"
#include "SelectionCharacterInstrument.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API ASelectionCharacterInstrument : public ACharacterInstrument
{
	GENERATED_BODY()

public:
	ASelectionCharacterInstrument();
	
	UPROPERTY(BlueprintReadWrite, Category = "Instrument State")
	UStaticMeshComponent* RootMesh;
	
	UPROPERTY(BlueprintReadWrite, Category = "Instrument State")
	UStaticMeshComponent* LinetraceMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instrument State",
		meta = (Bitmask, BitmaskEnum = "EInstrumentAvailableSelection"))
	uint8 AvailableSelections;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FSceneObjectSelection SelectedSceneObject;

	virtual void Use_Implementation() override;
};
