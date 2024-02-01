// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelType.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "LevelTransitionController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelLoadingEvent, ELevelType, Level);

class ULevelTransitionData;
class UPanelUI;

UCLASS(BlueprintType)
class PLANMODELLER3D_API ULevelTransitionController : public UObject, public IInitializable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FLevelLoadingEvent OnLevelStartedLoadingEvent;
	
	UPROPERTY(BlueprintAssignable)
	FLevelLoadingEvent OnLevelLoadedEvent;
	
	UPROPERTY(BlueprintAssignable)
	FLevelLoadingEvent OnLevelUnloadedEvent;
	
	UPROPERTY(BlueprintReadOnly)
	ELevelType CurrentLevelType;
	
public:
	virtual void Init_Implementation(UPrimaryDataAsset* TransitionData) override;
	
	UFUNCTION(BlueprintCallable)
	void LoadLevel(ELevelType LevelType);

	UFUNCTION(BlueprintCallable)
	void LoadStreamLevel(ELevelType LevelType);
	
private:
	UPROPERTY()
	ULevelTransitionData* Data;
	
	UPROPERTY()
	UPanelUI* LoadingScreen;

	UFUNCTION()
	void OnStreamLevelLoaded();

	UFUNCTION()
	void OnStartLoadingLevel(ELevelType Level);
	
	UFUNCTION()
	void OnLevelLoaded(ELevelType LevelType);

	UFUNCTION()
	void OnLevelUnloaded(ELevelType LevelType);
};
