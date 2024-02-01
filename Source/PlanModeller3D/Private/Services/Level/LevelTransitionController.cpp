// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Level/LevelTransitionController.h"
#include "Core/CoreFunctionLib.h"
#include "Kismet/GameplayStatics.h"
#include "Services/Level/LevelTransitionData.h"
#include "Services/UI/ManagerUI.h"


void ULevelTransitionController::Init_Implementation(UPrimaryDataAsset* TransitionData)
{
	IInitializable::Init_Implementation(TransitionData);
	Data = CastChecked<ULevelTransitionData>(TransitionData);

	OnLevelStartedLoadingEvent.AddDynamic(this, &ULevelTransitionController::OnStartLoadingLevel);
	OnLevelLoadedEvent.AddDynamic(this, &ULevelTransitionController::OnLevelLoaded);
	OnLevelUnloadedEvent.AddDynamic(this, &ULevelTransitionController::OnLevelUnloaded);
	
	LoadLevel(Data->InitialLevelType);
}

void ULevelTransitionController::LoadLevel(const ELevelType LevelType)
{
	if (LevelType == ELevelType::None)
	{
		UE_LOG(LogTemp, Error, TEXT("Level type is None"));
		return;
	}
	
	if (!Data->LevelPaths.Contains(LevelType))
	{
		UE_LOG(LogTemp, Error, TEXT("Level type %d not found in LevelPaths"), LevelType);
		return;
	}
	
	const FName LevelPath = Data->LevelPaths[LevelType];	
	UGameplayStatics::OpenLevel(this, LevelPath);
	CurrentLevelType = LevelType;
}

void ULevelTransitionController::LoadStreamLevel(ELevelType LevelType)
{
	if (LevelType == ELevelType::None)
	{
		UE_LOG(LogTemp, Error, TEXT("Level type is None"));
		return;
	}
	
	if (!Data->LevelPaths.Contains(LevelType))
	{
		UE_LOG(LogTemp, Error, TEXT("Level type %d not found in LevelPaths"), LevelType);
		return;
	}
	
	const FName LevelPath = Data->LevelPaths[LevelType];
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OnStreamLevelLoaded";
	LatentInfo.UUID = 0;
	LatentInfo.Linkage = 0;
	
	UGameplayStatics::LoadStreamLevel(this, LevelPath, true, true, LatentInfo);
	CurrentLevelType = LevelType;
}


// --------- Event handlers ----------
 
void ULevelTransitionController::OnStreamLevelLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("Stream level %s loaded"), *Data->LevelPaths[CurrentLevelType].ToString());
}

void ULevelTransitionController::OnStartLoadingLevel(ELevelType Level)
{
	UE_LOG(LogTemp, Warning, TEXT("Level %s started loading"), *Data->LevelPaths[Level].ToString());
	LoadingScreen = UCoreFunctionLib::GetManagerUI(this)->GetPanel(Data->LoadingScreenName, nullptr);
}

void ULevelTransitionController::OnLevelLoaded(ELevelType Level)
{
	UE_LOG(LogTemp, Warning, TEXT("Level %s loaded"), *Data->LevelPaths[Level].ToString());
	if (LoadingScreen)
	{
		UCoreFunctionLib::GetManagerUI(this)->ReturnPanel(LoadingScreen);
		LoadingScreen = nullptr;
	}
}

void ULevelTransitionController::OnLevelUnloaded(ELevelType Level)
{
	UE_LOG(LogTemp, Warning, TEXT("Level %s unloaded"), *Data->LevelPaths[Level].ToString());
}
