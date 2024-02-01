// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Level/LevelLoadGameState.h"
#include "Core/CoreFunctionLib.h"
#include "Services/Level/LevelTransitionController.h"


void ALevelLoadGameState::BeginPlay()
{
	Super::BeginPlay();
	
	TransitionController = UCoreFunctionLib::GetTransitionController(this);
	LevelType = TransitionController->CurrentLevelType;

	if (LevelType != ELevelType::None)
	{
		TransitionController->OnLevelStartedLoadingEvent.Broadcast(LevelType);
	}
	
	LoadLevel();
	
	if (LevelType != ELevelType::None)
	{
		TransitionController->OnLevelLoadedEvent.Broadcast(LevelType);
	}
}

void ALevelLoadGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (LevelType != ELevelType::None && TransitionController != nullptr)
	{
		TransitionController->OnLevelUnloadedEvent.Broadcast(LevelType);
	}
}

void ALevelLoadGameState::LoadLevel_Implementation() { }
