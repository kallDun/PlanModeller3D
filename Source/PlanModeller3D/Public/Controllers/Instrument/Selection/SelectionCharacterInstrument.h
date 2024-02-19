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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instrument State",
		meta = (Bitmask, BitmaskEnum = "EInstrumentAvailableSelection"))
	uint8 AvailableSelections;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FSceneObjectSelection SelectedSceneObject;

	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FSceneObjectSelection PreviewedSceneObject;

	virtual void Use_Implementation() override;

	virtual void Preview_Implementation() override;

protected:
	UFUNCTION()
	AActor* GetHitActorFromLinetrace() const;
	
	UFUNCTION()
	FSceneObjectSelection GetSelectionFromHitActor(AActor* HitActor);
};
