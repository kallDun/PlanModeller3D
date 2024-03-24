// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInstrument.h"
#include "Models/Furnitures/FurnitureData.h"
#include "Models/Instrument/FurnitureInstrumentType.h"
#include "Models/Plan3D/MFurniture.h"
#include "FurnitureCharacterInstrument.generated.h"

struct FMFurniture;
class USavingService;
class UFurnitureController;
struct FFurnitureData;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API AFurnitureCharacterInstrument : public ACharacterInstrument
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	EFurnitureInstrumentType InstrumentType;

	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FFurnitureData FurnitureData;

	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	FString FurniturePreviewID;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	int FurnitureVariationIndex;
	
	UPROPERTY(BlueprintReadOnly, Category = "Instrument State")
	TArray<FString> Library;

protected:
	UPROPERTY()
	UFurnitureController* FurnitureController;

	UPROPERTY()
	USavingService* SavingService;

private:
	UPROPERTY()
	FVector HitPointOffset;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	FRotator SetupRotation;

	UPROPERTY()
	FString SavedSelectedRoomIDbyWall;

	UPROPERTY()
	FMFurniture SavedFurnitureData;

public:
	virtual void Activate(APMCharacter* InCharacter) override;
	
	virtual void Input_Implementation(FInstrumentInputData InputData) override;

	virtual void Deactivate() override;

	UFUNCTION(BlueprintCallable)
	void InitSpawnFromLibrary(TArray<FString> InLibrary, FString InFurnitureName, int VariationIndex);

	UFUNCTION(BlueprintCallable)
	void InitSpawnFromLibraryFromStart(TArray<FString> InLibrary);

	UFUNCTION(BlueprintCallable)
	void InitSpawnWithoutLibrary(FString InFurnitureName, int VariationIndex);

	UFUNCTION(BlueprintCallable)
	void InitUpdateConcrete(const FString Id, const FMFurniture InFurnitureSaveData);

protected:
	UFUNCTION()
	FFurnitureData GetFurnitureDataFromName(const FString Name) const;
	
	UFUNCTION()
	FVector GetHitPointFromLinetrace(bool& bHit, FString& SelectedRoomID);

	UFUNCTION()
	void AddOrUpdatePreviewFurniture(const FFurnitureData Data, const FVector& InHitPoint, FString SelectedRoomID) const;
	
	UFUNCTION()
	void RemovePreviewFurniture() const;

	UFUNCTION()
	bool IsFurniturePreviewValid() const;
};
