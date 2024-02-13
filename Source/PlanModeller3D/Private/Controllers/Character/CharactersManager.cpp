// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/CharactersManager.h"
#include "Controllers/Character/CharactersManagerData.h"
#include "Controllers/Character/PMCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCharactersManager::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UCharactersManagerData>(DataAsset);

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	for (auto CharacterClass : Data->CharacterClasses)
	{
		const auto Character = GetWorld()->SpawnActor<APMCharacter>(CharacterClass);
		Character->Init(this);
		Characters.Add(Character);
	}
	Characters[Data->DefaultCharacterIndex]->SelectAsCurrent();
}

APMCharacter* UCharactersManager::GetCurrentCharacter() const
{
	for (const auto Character : Characters)
	{
		if (Character->GetIsCurrentCharacter())
		{
			return Character;
		}
	}
	return nullptr;
}
