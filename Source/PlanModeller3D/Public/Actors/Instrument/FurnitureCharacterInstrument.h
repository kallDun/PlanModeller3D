// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInstrument.h"
#include "Models/Furnitures/FurnitureData.h"
#include "FurnitureCharacterInstrument.generated.h"


class USavingService;
class UFurnitureController;
struct FFurnitureData;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API AFurnitureCharacterInstrument : public ACharacterInstrument
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UFurnitureController* FurnitureController;

	UPROPERTY()
	USavingService* SavingService;

protected:
	UPROPERTY()
	FVector HitPointOffset;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	FString FurniturePreviewID;
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FString FurnitureName;

	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FFurnitureData FurnitureData;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	int FurnitureVariationIndex;

	UFUNCTION(BlueprintCallable)
	void SetFurnitureData(FString InFurnitureName, int VariationIndex);

public:
	virtual void Activate(APMCharacter* InCharacter) override;
	
	virtual void Input_Implementation(FInstrumentInputData InputData) override;

	virtual void Deactivate() override;

protected:	
	UFUNCTION()
	FVector GetHitPointFromLinetrace(bool& bHit) const;

	UFUNCTION()
	void AddOrUpdatePreviewFurniture(const FFurnitureData Data, const FVector& InHitPoint) const;
	
	UFUNCTION()
	void RemovePreviewFurniture() const;

	UFUNCTION()
	bool IsFurniturePreviewValid() const;
};
