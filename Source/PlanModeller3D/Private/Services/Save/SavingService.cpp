// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Save/SavingService.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "Services/Save/Data/SaveGameData.h"
#include "Models/Plan/DMPlan.h"
#include "Services/Save/SavingServiceData.h"


void USavingService::Init(USavingServiceData* SavingServiceData)
{
	Data = SavingServiceData;
	SaveGames = GetSaveGames(Data->SlotsCount);
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
	SaveGames = GetSaveGames(Data->SlotsCount);
}

void USavingService::DeleteSave(const int SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= SaveGames.Num()) return;
	UGameplayStatics::DeleteGameInSlot(FString::FromInt(SlotIndex), 0);
	SaveGames = GetSaveGames(Data->SlotsCount);
}

void USavingService::CreateNewSaveGame(const int SlotIndex, FString SaveName, const FString FilePath)
{
	USaveGameData* NewSaveGame = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	NewSaveGame->SaveName = SaveName;
	CurrentSaveGame = NewSaveGame;

	if (FString FileData = ""; FFileHelper::LoadFileToString(FileData, *FilePath))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct<FDMPlan>(FileData, &NewSaveGame->Plan2D, 0, 0);
	}
	SaveGame(SlotIndex);
}
