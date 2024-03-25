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
#include "Utils/Vector2DArray.h"
#include "Utils/Vector2D_MathLib.h"


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
	SetupRotation = FRotator::ZeroRotator;
	SavedSelectedRoomIDbyWall = "";
}

void AFurnitureCharacterInstrument::Deactivate()
{
	RemovePreviewFurniture();
	if (InstrumentType == EFurnitureInstrumentType::UpdateConcrete
		&& !SavingService->CurrentSaveGame->Plan3D.Furnitures.Contains(FurniturePreviewID))
	{
		SavingService->CurrentSaveGame->Plan3D.Furnitures.Add(FurniturePreviewID, SavedFurnitureData);
		SavingService->CurrentSaveGame->OnModelChanged.Broadcast(ECrudActionType::Create, EPlanModelType::Furniture, FurniturePreviewID);
	}

	Super::Deactivate();
}

// ------------------------------------ INIT ------------------------------------

void AFurnitureCharacterInstrument::InitSpawnFromLibrary(const TArray<FFurnitureLibraryFolder> InLibrary, const FString InFurnitureName, const int VariationIndex)
{
	InstrumentType = EFurnitureInstrumentType::SpawnFromLibrary;
	Library = InLibrary;
	SavedFurnitureData = FMFurniture();
	FurnitureVariationIndex = VariationIndex;
	FurniturePreviewID = SavingService->CurrentSaveGame->GetUniqueFurnitureID();
	FurnitureData = GetFurnitureDataFromName(InFurnitureName);
	InputTypes = static_cast<int32>(
		EInstrumentInputType::TriggerExitInput
		| EInstrumentInputType::TriggerUseInput
		| EInstrumentInputType::TriggerPreviewInput
		| EInstrumentInputType::TwoAxisInput
		| EInstrumentInputType::OneAxisInput
		| EInstrumentInputType::TriggerNextInput
		| EInstrumentInputType::TriggerPreviousInput);
}

void AFurnitureCharacterInstrument::InitSpawnFromLibraryFromStart(const TArray<FFurnitureLibraryFolder> InLibrary)
{
	InitSpawnFromLibrary(InLibrary, Library[0].Furnitures[0].Name, 0);
}

void AFurnitureCharacterInstrument::InitSpawnWithoutLibrary(FString InFurnitureName, int VariationIndex)
{
	InstrumentType = EFurnitureInstrumentType::SpawnWithoutLibrary;
	Library = {};
	SavedFurnitureData = FMFurniture();
	FurnitureVariationIndex = VariationIndex;
	FurniturePreviewID = SavingService->CurrentSaveGame->GetUniqueFurnitureID();
	FurnitureData = GetFurnitureDataFromName(InFurnitureName);
	InputTypes = static_cast<int32>(
		EInstrumentInputType::TriggerExitInput
		| EInstrumentInputType::TriggerUseInput
		| EInstrumentInputType::TriggerPreviewInput
		| EInstrumentInputType::TwoAxisInput
		| EInstrumentInputType::OneAxisInput);
}

void AFurnitureCharacterInstrument::InitUpdateConcrete(const FString Id, const FMFurniture InFurnitureSaveData)
{
	InstrumentType = EFurnitureInstrumentType::UpdateConcrete;
	SavedFurnitureData = InFurnitureSaveData;
	FurnitureVariationIndex = InFurnitureSaveData.VariationIndex;
	FurniturePreviewID = Id;
	FurnitureData = GetFurnitureDataFromName(InFurnitureSaveData.Name);
	Library = {};
	InputTypes = static_cast<int32>(
		EInstrumentInputType::TriggerExitInput
		| EInstrumentInputType::TriggerUseInput
		| EInstrumentInputType::TriggerPreviewInput
		| EInstrumentInputType::TwoAxisInput
		| EInstrumentInputType::OneAxisInput);
}

// ------------------------------------ INPUT ------------------------------------

void AFurnitureCharacterInstrument::Input_Implementation(FInstrumentInputData InputData)
{
	Super::Input_Implementation(InputData);
	
	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerUseInput)
		&& InputData.UseInput)
	{
		if (FurnitureData.Name.IsEmpty()) return;
		bool bHit = false;
		FString SelectedRoomID;
		const FVector HitPoint = GetHitPointFromLinetrace(bHit, SelectedRoomID);
		if (bHit)
		{
			AddOrUpdatePreviewFurniture(FurnitureData, HitPoint, SelectedRoomID);
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
		if (FurnitureData.Name.IsEmpty()) return;
		bool bHit = false;
		FString SelectedRoomID;
		const FVector HitPoint = GetHitPointFromLinetrace(bHit, SelectedRoomID);
		if (bHit)
		{
			AddOrUpdatePreviewFurniture(FurnitureData, HitPoint, SelectedRoomID);
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

	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerNextInput) &&
		InputData.TriggerNextInput && InstrumentType == EFurnitureInstrumentType::SpawnFromLibrary)
	{
		HitPointOffset = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
		SetupRotation = FRotator::ZeroRotator;
		SavedSelectedRoomIDbyWall = "";

		if (Library.Num() == 0) return;
		if (FurnitureVariationIndex + 1 < FurnitureData.Variations.Num())
		{
			RemovePreviewFurniture();
			FurnitureVariationIndex++;
			OnInstrumentDataUpdated.Broadcast();
		}
		else
		{
			int LibraryIndex = 0;
			int FurnitureIndex = 0;
			bool bFound = false;
			for (int i = 0; i < Library.Num(); i++)
			{
				for (int j = 0; j < Library[i].Furnitures.Num(); j++)
				{
					if (Library[i].Furnitures[j].Name == FurnitureData.Name)
					{
						LibraryIndex = i;
						FurnitureIndex = j;
						bFound = true;
						break;
					}
				}
				if (bFound) break;
			}

			if (bFound && FurnitureIndex + 1 < Library[LibraryIndex].Furnitures.Num())
			{
				RemovePreviewFurniture();
				FurnitureVariationIndex = 0;
				FurnitureData = GetFurnitureDataFromName(
					Library[LibraryIndex]
					.Furnitures[FurnitureIndex + 1]
					.Name);
				OnInstrumentDataUpdated.Broadcast();
			}
			else if (bFound && LibraryIndex + 1 < Library.Num())
			{
				RemovePreviewFurniture();
				FurnitureVariationIndex = 0;
				FurnitureData = GetFurnitureDataFromName(
					Library[LibraryIndex + 1]
					.Furnitures[0]
					.Name);
				OnInstrumentDataUpdated.Broadcast();
			}
		}
	}

	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerPreviousInput) &&
		InputData.TriggerPreviousInput && InstrumentType == EFurnitureInstrumentType::SpawnFromLibrary)
	{
		HitPointOffset = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
		SetupRotation = FRotator::ZeroRotator;
		SavedSelectedRoomIDbyWall = "";

		if (Library.Num() == 0) return;
		if (FurnitureVariationIndex > 0)
		{
			RemovePreviewFurniture();
			FurnitureVariationIndex--;
			OnInstrumentDataUpdated.Broadcast();
		}
		else
		{
			int LibraryIndex = 0;
			int FurnitureIndex = 0;
			bool bFound = false;
			for (int i = 0; i < Library.Num(); i++)
			{
				for (int j = 0; j < Library[i].Furnitures.Num(); j++)
				{
					if (Library[i].Furnitures[j].Name == FurnitureData.Name)
					{
						LibraryIndex = i;
						FurnitureIndex = j;
						bFound = true;
						break;
					}
				}
				if (bFound) break;
			}

			if (bFound && FurnitureIndex - 1 >= 0)
			{
				RemovePreviewFurniture();
				FurnitureData = GetFurnitureDataFromName(
					Library[LibraryIndex]
					.Furnitures[FurnitureIndex - 1]
					.Name);
				FurnitureVariationIndex = FurnitureData.Variations.Num() - 1;
				OnInstrumentDataUpdated.Broadcast();
			}
			else if (bFound && LibraryIndex - 1 >= 0)
			{
				RemovePreviewFurniture();
				FurnitureData = GetFurnitureDataFromName(
					Library[LibraryIndex - 1]
					.Furnitures[Library[LibraryIndex - 1].Furnitures.Num() - 1]
					.Name);
				FurnitureVariationIndex = FurnitureData.Variations.Num() - 1;
				OnInstrumentDataUpdated.Broadcast();
			}
		}
	}
}

// ------------------------------------ PRIVATE ------------------------------------

FFurnitureData AFurnitureCharacterInstrument::GetFurnitureDataFromName(const FString Name) const
{
	TArray<FFurnitureData> Furnitures = FurnitureController->GetFurnituresData();
	const auto Data = Furnitures.FindByPredicate([Name](const FFurnitureData& Furniture)
	{
		return Furniture.Name == Name;
	});
	if (Data != nullptr)
	{
		return *Data;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("FurnitureCharacterInstrument::SetFurnitureData: Furniture data not found!"));
		return FFurnitureData();
	}
}

FVector AFurnitureCharacterInstrument::GetHitPointFromLinetrace(bool& bHit, FString& SelectedRoomID)
{
	auto [Start, End] = Character->GetInstrumentLinetraceRay();
	auto Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Character);
	Params.bTraceComplex = true;

	auto Hit = FHitResult();
	if (GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ECC_GameTraceChannel2, Params))
	{
		if (Hit.GetActor() && Hit.GetActor()->IsA(AFoundationActor::StaticClass()))
		{
			if (FurnitureData.PlacementType == EFurniturePlacementType::Floor
					&& Hit.GetActor()->IsA(ARoomActor::StaticClass()))
			{
				auto Room = Cast<ARoomActor>(Hit.GetActor());
				SelectedRoomID = Room->DMRoom.Id;
				SetupRotation = FRotator::ZeroRotator;
				SavedSelectedRoomIDbyWall = "";
				bHit = true;
				return Hit.ImpactPoint;
			}
			if (FurnitureData.PlacementType == EFurniturePlacementType::Wall
				&& Hit.GetActor()->IsA(AWallActor::StaticClass()))
			{
				auto Wall = Cast<AWallActor>(Hit.GetActor());
				SelectedRoomID = Wall->GetClosestRoomID(Hit.ImpactPoint);

				if (SavedSelectedRoomIDbyWall != SelectedRoomID)
				{
					FVector2D ForwardVector = UVector2D_MathLib::GetDirectionVectorFromWallToRoom(
					FVector2DArray(Wall->DMWall.Points),FVector2DArray(SavingService->CurrentSaveGame->GetRoom(SelectedRoomID).Points),
					this);
					SetupRotation = UVector2D_MathLib::GetRotationFromDirectionVector(ForwardVector);
				}
				
				bHit = true;
				return Hit.ImpactPoint;
			}
		}
	}
	bHit = false;
	return FVector::ZeroVector;
}

void AFurnitureCharacterInstrument::AddOrUpdatePreviewFurniture(const FFurnitureData Data, const FVector& InHitPoint, FString SelectedRoomID) const
{
	const FVector SpawnPoint = InHitPoint + HitPointOffset;
	const FRotator SpawnRotation = Rotation + SetupRotation;
	const FMFurniture Furniture = FMFurniture(Data.Name, SpawnPoint,
		SpawnRotation, FurnitureVariationIndex, SelectedRoomID, true, false);
	
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
