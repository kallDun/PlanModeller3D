// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SavingService.generated.h"


class USaveGameData;

UCLASS(Blueprintable, BlueprintType)
class PLANMODELLER3D_API USavingService : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<USaveGameData*> SaveGames;

	UPROPERTY(BlueprintReadOnly)
	USaveGameData* CurrentSaveGame;
	
	UFUNCTION()
	void Init(const int SlotsToLoad);
	
	UFUNCTION()
	static TArray<USaveGameData*> GetSaveGames(const int SlotsToLoad);

	UFUNCTION(BlueprintCallable)
	void LoadGame(int SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	void SaveGame(int SlotIndex);

	UFUNCTION(BlueprintCallable)
	void CreateNewSaveGame(int SlotIndex, FString SaveName, FString FilePath);
};
