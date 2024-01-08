// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelTransitionController.h"
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
	UGameplayStatics::OpenLevel(GetWorld(), LevelPath, true);
}
