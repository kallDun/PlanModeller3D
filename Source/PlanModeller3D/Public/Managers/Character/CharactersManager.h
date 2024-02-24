// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "CharactersManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterAction, APMCharacter*, Character);

class APMCharacter;
class UCharactersManagerData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UCharactersManager : public UObject, public IInitializable
{
	GENERATED_BODY()
	UCharactersManager() = default;

protected:
	UPROPERTY()
	UCharactersManagerData* Data;
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<APMCharacter*> Characters = {};

	UPROPERTY(BlueprintAssignable)
	FCharacterAction OnBeforeCharacterSelected;
	
	UPROPERTY(BlueprintAssignable)
	FCharacterAction OnCharacterSelected;

	UPROPERTY(BlueprintReadOnly)
	APlayerController* PlayerController;

	virtual void Init_Implementation(UPrimaryDataAsset* DataAsset) override;

	UFUNCTION(BlueprintCallable)
	APMCharacter* GetCurrentCharacter() const;
	
};
