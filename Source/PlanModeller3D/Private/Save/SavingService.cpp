// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SavingService.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "Save/Data/SaveGameData.h"
#include "Utils/Deserialization/DeserializationFuncLib.h"


void USavingService::Init(const int SlotsToLoad)
{
	SaveGames = GetSaveGames(SlotsToLoad);
}

TArray<USaveGameData*> USavingService::GetSaveGames(const int SlotsToLoad)
{
	TArray<USaveGameData*> SaveGames = {};
	for (int i = 0; i < SlotsToLoad; i++)
	{
		SaveGames.Add(Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(FString::FromInt(i), 0)));
	}
	return SaveGames;
}

void USavingService::LoadGame(const int SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= SaveGames.Num()) return;
	CurrentSaveGame = SaveGames[SlotIndex];
}

void USavingService::SaveGame(const int SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= SaveGames.Num()) return;
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, FString::FromInt(SlotIndex), 0);
	Init(SaveGames.Num());
}

void USavingService::CreateNewSaveGame(const int SlotIndex, FString SaveName, const FString FilePath)
{
	USaveGameData* NewSaveGame = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	NewSaveGame->SaveName = SaveName;
	CurrentSaveGame = NewSaveGame;

	TSharedPtr<FJsonObject> OutJsonObject = MakeShareable(new FJsonObject());
	UDeserializationFuncLib::DeserializeJsonFile(FilePath, OutJsonObject);
	FJsonObjectConverter::JsonObjectToUStruct<FDMPlan>(OutJsonObject.ToSharedRef(), &NewSaveGame->Plan2D);
	
	SaveGame(SlotIndex);
}
