// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelTransitionController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ULevelTransitionController::LoadLevel(const ELevelType LevelType)
{
	if (!LevelPaths.Contains(LevelType))
	{
		UE_LOG(LogTemp, Error, TEXT("Level type %d not found in LevelPaths"), LevelType);
		return;
	}
	
	const FName LevelPath = LevelPaths[LevelType];
	UE_LOG(LogTemp, Warning, TEXT("Loading level %s"), *LevelPath.ToString());

	UGameplayStatics::OpenLevel(this, LevelPath);
}

void ULevelTransitionController::LoadStreamLevel(ELevelType LevelType)
{
	if (!LevelPaths.Contains(LevelType))
	{
		UE_LOG(LogTemp, Error, TEXT("Level type %d not found in LevelPaths"), LevelType);
		return;
	}
	
	const FName LevelPath = LevelPaths[LevelType];
	UE_LOG(LogTemp, Warning, TEXT("Loading level %s"), *LevelPath.ToString());
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OnLevelLoaded";
	LatentInfo.UUID = 0;
	LatentInfo.Linkage = 0;

	UGameplayStatics::LoadStreamLevel(this, LevelPath, true, true, LatentInfo);
	CreateLoadingScreen();
}

void ULevelTransitionController::CreateLoadingScreen()
{
	LoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenClass, FName("Loading Screen"));
	LoadingScreen->AddToViewport();
}

void ULevelTransitionController::OnLevelLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("Level loaded"));
	LoadingScreen->RemoveFromParent();
	LoadingScreen->Destruct();
	LoadingScreen = nullptr;
}
