// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "SavingService.generated.h"


class USavingServiceData;
class USaveGameData;

UCLASS(Blueprintable, BlueprintType)
class PLANMODELLER3D_API USavingService : public UObject, public IInitializable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	USavingServiceData* Data;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<USaveGameData*> SaveGames;

	UPROPERTY(BlueprintReadOnly)
	USaveGameData* CurrentSaveGame;

	virtual void Init_Implementation(UPrimaryDataAsset* SavingServiceData) override;
	
	UFUNCTION()
	static TArray<USaveGameData*> GetSaveGames(const int SlotsToLoad);

	UFUNCTION(BlueprintCallable)
	void LoadGame(int SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	void SaveGame(int SlotIndex);

	UFUNCTION(BlueprintCallable)
	void DeleteSave(int SlotIndex);

	UFUNCTION(BlueprintCallable)
	void CreateNewSaveGame(int SlotIndex, FString SaveName, FString FilePath);
};
