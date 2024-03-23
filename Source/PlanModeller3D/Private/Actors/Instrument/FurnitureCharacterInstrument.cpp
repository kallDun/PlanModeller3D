// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Instrument/FurnitureCharacterInstrument.h"
#include "Actors/Character/PMCharacter.h"
#include "Actors/Foundation/FoundationActor.h"
#include "Actors/Foundation/RoomActor.h"
#include "Actors/Foundation/WallActor.h"
#include "Core/CoreFunctionLib.h"
#include "Managers/Furnitures/FurnitureController.h"
#include "Managers/Instrument/InstrumentsManager.h"
#include "Models/Instrument/InstrumentInputData.h"
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
	FurniturePreviewID = SavingService->CurrentSaveGame->GetUniqueFurnitureID();
}

void AFurnitureCharacterInstrument::Input_Implementation(FInstrumentInputData InputData)
{
	Super::Input_Implementation(InputData);
	
	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerUseInput)
		&& InputData.UseInput)
	{
		if (FurnitureName.IsEmpty() || FurnitureData.Name.IsEmpty()) return;
		bool bHit = false;
		const FVector HitPoint = GetHitPointFromLinetrace(bHit);
		if (bHit)
		{
			AddOrUpdatePreviewFurniture(FurnitureData, HitPoint);
		}
		
		if (IsFurniturePreviewValid())
		{
			OnInstrumentUsed.Broadcast();
			SavingService->CurrentSaveGame->Plan3D.Furnitures[FurniturePreviewID].IsPreview = false;
			SavingService->CurrentSaveGame->OnModelChanged.Broadcast(ECrudActionType::Update, EPlanModelType::Furniture, FurniturePreviewID);
			Manager->DeactivateCurrentInstrument();
		}
	}

	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerPreviewInput)
		&& InputData.PreviewInput)
	{
		if (FurnitureName.IsEmpty() || FurnitureData.Name.IsEmpty()) return;
		bool bHit = false;
		const FVector HitPoint = GetHitPointFromLinetrace(bHit);
		if (bHit)
		{
			AddOrUpdatePreviewFurniture(FurnitureData, HitPoint);
		}
	}

	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TwoAxisInput) &&
		InputData.TwoAxisInput.IsZero() == false)
	{
		HitPointOffset += FVector(InputData.TwoAxisInput.X, InputData.TwoAxisInput.Y, 0);
	}

	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::OneAxisInput) &&
		InputData.OneAxisInput != 0)
	{
		Rotation.Yaw += InputData.OneAxisInput * 5;
	}
}

void AFurnitureCharacterInstrument::SetFurnitureData(const FString InFurnitureName, const int VariationIndex)
{
	FurnitureName = InFurnitureName;
	FurnitureVariationIndex = VariationIndex;

	TArray<FFurnitureData> Furnitures = FurnitureController->GetFurnituresData();
	const auto Data = Furnitures.FindByPredicate([this](const FFurnitureData& Furniture)
	{
		return Furniture.Name == FurnitureName;
	});
	if (Data != nullptr) FurnitureData = *Data;
	else UE_LOG(LogTemp, Error, TEXT("FurnitureCharacterInstrument::SetFurnitureData: Furniture data not found!"));
}

void AFurnitureCharacterInstrument::Deactivate()
{
	Super::Deactivate();
	RemovePreviewFurniture();
}

FVector AFurnitureCharacterInstrument::GetHitPointFromLinetrace(bool& bHit) const
{
	auto [Start, End] = Character->GetInstrumentLinetraceRay();
	auto Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Character);
	Params.bTraceComplex = true;

	auto Hit = FHitResult();
	if (GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ECC_GameTraceChannel2, Params))
	{
		if (Hit.GetActor())
		{
			if (Hit.GetActor()->IsA(AFoundationActor::StaticClass()))
			{
				if (FurnitureData.PlacementType == EFurniturePlacementType::Floor
					&& Hit.GetActor()->IsA(ARoomActor::StaticClass()))
				{
					bHit = true;
					return Hit.ImpactPoint;
				}
				if (FurnitureData.PlacementType == EFurniturePlacementType::Wall
					&& Hit.GetActor()->IsA(AWallActor::StaticClass()))
				{
					bHit = true;
					return Hit.ImpactPoint;
				}
			}			
		}
	}
	bHit = false;
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
		SavingService->CurrentSaveGame->OnModelChanged.Broadcast(ECrudActionType::Delete, EPlanModelType::Furniture, FurniturePreviewID);
		SavingService->CurrentSaveGame->Plan3D.Furnitures.Remove(FurniturePreviewID);
	}
}

bool AFurnitureCharacterInstrument::IsFurniturePreviewValid() const
{
	if (!SavingService->CurrentSaveGame->Plan3D.Furnitures.Contains(FurniturePreviewID)) return false;
	return SavingService->CurrentSaveGame->Plan3D.Furnitures[FurniturePreviewID].IsCorrectlyPlaced;
}
