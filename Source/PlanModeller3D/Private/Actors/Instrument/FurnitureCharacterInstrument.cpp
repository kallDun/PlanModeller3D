// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Instrument/FurnitureCharacterInstrument.h"
#include "Actors/Character/PMCharacter.h"
#include "Core/CoreFunctionLib.h"
#include "Managers/Furnitures/FurnitureController.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Services/Save/SavingService.h"


void AFurnitureCharacterInstrument::Activate(APMCharacter* InCharacter)
{
	Super::Activate(InCharacter);
	if (!FurnitureController)
	{
		FurnitureController = UCoreFunctionLib::GetFurnitureController(this);
	}
	if (!SavingService)
	{
		SavingService = UCoreFunctionLib::GetSavingService(this);
	}
	HitPointOffset = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;
}

void AFurnitureCharacterInstrument::SetFurnitureData(const FName InFurnitureName, const int VariationIndex)
{
	FurnitureName = InFurnitureName;
	FurnitureVariationIndex = VariationIndex;
}

void AFurnitureCharacterInstrument::Use_Implementation()
{
	Super::Use_Implementation();
	if (FurnitureName.IsNone()) return;
	bool bFoundData = false;
	const FFurnitureData Data = GetFurnitureData(bFoundData);
	if (!bFoundData) return;
	bool bHit = false;
	const FVector HitPoint = GetHitPointFromLinetrace(bHit);
	if (bHit)
	{
		AddOrUpdatePreviewFurniture(Data, HitPoint);
	}
}

void AFurnitureCharacterInstrument::Preview_Implementation()
{
	Super::Preview_Implementation();
	if (FurnitureName.IsNone()) return;
	bool bFoundData = false;
	const FFurnitureData Data = GetFurnitureData(bFoundData);
	if (!bFoundData) return;
	bool bHit = false;
	const FVector HitPoint = GetHitPointFromLinetrace(bHit);
	if (bHit)
	{
		AddOrUpdatePreviewFurniture(Data, HitPoint);
	}
}

void AFurnitureCharacterInstrument::Deactivate()
{
	Super::Deactivate();
	RemovePreviewFurniture();
}

FFurnitureData AFurnitureCharacterInstrument::GetFurnitureData(bool& bFound) const
{
	const auto Data = FurnitureController->GetFurnituresData().FindByPredicate([this](const FFurnitureData& Data)
	{
		return Data.Name == FurnitureName;
	});
	bFound = Data != nullptr;
	if (bFound) return *Data;
	return FFurnitureData();
}

FVector AFurnitureCharacterInstrument::GetHitPointFromLinetrace(bool& bHit) const
{
	// make linetrace, get hit actor, check if it's a valid selection, if it is, set it as current selection
	// if it's not a valid selection, do nothing
	auto [Start, End] = Character->GetInstrumentLinetraceRay();
	auto Hit = FHitResult(ForceInit);
	auto Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Character);
	Params.bTraceComplex = true;

	bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
	if (bHit)
	{
		return Hit.ImpactPoint;
	}
	return FVector::ZeroVector;
}

void AFurnitureCharacterInstrument::AddOrUpdatePreviewFurniture(const FFurnitureData Data, const FVector& InHitPoint) const
{
	const FVector SpawnPoint = InHitPoint + HitPointOffset;
	const FRotator SpawnRotation = Rotation;
	const FMFurniture Furniture = FMFurniture(Data.Name, SpawnPoint, SpawnRotation, FurnitureVariationIndex, true, false);
	
	if (SavingService->CurrentSaveGame->Plan3D.Furnitures.Contains(FurniturePreviewID))
	{
		SavingService->CurrentSaveGame->Plan3D.Furnitures[FurniturePreviewID] = Furniture;
		SavingService->CurrentSaveGame->OnModelChanged.Broadcast(ECrudActionType::Update, EPlanModelType::Furniture, FurniturePreviewID);
	}
	else
	{
		SavingService->CurrentSaveGame->Plan3D.Furnitures.Add(FurniturePreviewID, Furniture);
		SavingService->CurrentSaveGame->OnModelChanged.Broadcast(ECrudActionType::Create, EPlanModelType::Furniture, FurniturePreviewID);
	}
}

void AFurnitureCharacterInstrument::RemovePreviewFurniture() const
{
	if (!SavingService->CurrentSaveGame->Plan3D.Furnitures.Contains(FurniturePreviewID)) return;
	if (SavingService->CurrentSaveGame->Plan3D.Furnitures[FurniturePreviewID].IsPreview)
	{
		SavingService->CurrentSaveGame->Plan3D.Furnitures.Remove(FurniturePreviewID);
		SavingService->CurrentSaveGame->OnModelChanged.Broadcast(ECrudActionType::Delete, EPlanModelType::Furniture, FurniturePreviewID);
	}
}

bool AFurnitureCharacterInstrument::IsFurniturePreviewValid() const
{
	if (!SavingService->CurrentSaveGame->Plan3D.Furnitures.Contains(FurniturePreviewID)) return false;
	return SavingService->CurrentSaveGame->Plan3D.Furnitures[FurniturePreviewID].IsCorrectlyPlaced;
}
