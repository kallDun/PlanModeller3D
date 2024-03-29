// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInstrument.h"
#include "Models/Instrument/SceneObjectSelection.h"
#include "SelectionCharacterInstrument.generated.h"

class IActorSelectable;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API ASelectionCharacterInstrument : public ACharacterInstrument
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AActor* PreviewedActor;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instrument State",
		meta = (Bitmask, BitmaskEnum = "EInstrumentAvailableSelection"))
	uint8 AvailableSelections;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FSceneObjectSelection SelectedSceneObject;

	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FSceneObjectSelection PreviewedSceneObject;

	virtual void Input_Implementation(FInstrumentInputData InputData) override;

	virtual void Deactivate() override;

protected:
	UFUNCTION()
	AActor* GetHitActorFromLinetrace() const;
};
