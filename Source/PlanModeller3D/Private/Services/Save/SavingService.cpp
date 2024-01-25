// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Save/SavingService.h"
#include "Kismet/GameplayStatics.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Services/Save/SavingServiceData.h"


void USavingService::Init_Implementation(UPrimaryDataAsset* SavingServiceData)
{
	IInitializable::Init_Implementation(SavingServiceData);
	Data = Cast<USavingServiceData>(SavingServiceData);
	SaveGames = GetSaveGames(Data->SlotsCount);
}

TArray<UPlanModellerSaveData*> USavingService::GetSaveGames(const int SlotsToLoad)
{
	TArray<UPlanModellerSaveData*> SaveGames = {};
	for (int i = 0; i < SlotsToLoad; i++)
	{
		SaveGames.Add(Cast<UPlanModellerSaveData>(UGameplayStatics::LoadGameFromSlot(FString::FromInt(i), 0)));
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
	UPlanModellerSaveData* NewSaveGame = Cast<UPlanModellerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlanModellerSaveData::StaticClass()));
	NewSaveGame->FilePath = FilePath;
	NewSaveGame->Init(SaveName);
	
	NewSaveGame->SaveName = SaveName;
	CurrentSaveGame = NewSaveGame;
	
	SaveGame(SlotIndex);
}
