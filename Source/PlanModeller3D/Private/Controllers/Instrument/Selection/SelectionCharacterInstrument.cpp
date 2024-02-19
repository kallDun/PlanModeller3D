// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Instrument/Selection/SelectionCharacterInstrument.h"
#include "Actors/Foundation/RoomActor.h"
#include "Actors/Foundation/WallActor.h"
#include "Actors/Furnitures/Furniture.h"
#include "Components/StaticMeshComponent.h"


void ASelectionCharacterInstrument::Use_Implementation()
{
	SelectedSceneObject = GetSelectionFromHitActor(GetHitActorFromLinetrace());
	Super::Use_Implementation();
}

void ASelectionCharacterInstrument::Preview_Implementation()
{
	const auto HitActor = GetHitActorFromLinetrace();
	PreviewedSceneObject = GetSelectionFromHitActor(HitActor);
}

AActor* ASelectionCharacterInstrument::GetHitActorFromLinetrace() const
{
	// make linetrace, get hit actor, check if it's a valid selection, if it is, set it as current selection
	// if it's not a valid selection, do nothing
	auto Component = Character->GetLinetraceInstrumentCastComponent();
	auto Start = Component->GetComponentLocation();
	auto End = Start + (Component->GetForwardVector() * 1000);
	auto Hit = FHitResult(ForceInit);
	auto Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Character);
	Params.bTraceComplex = true;

	if (bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (auto HitActor = Hit.GetActor())
		{
			return HitActor;
		}
	}
	return nullptr;
}

FSceneObjectSelection ASelectionCharacterInstrument::GetSelectionFromHitActor(AActor* HitActor)
{
	if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
				EInstrumentAvailableSelection::IAS_Room))
	{
		if (const auto Room = Cast<ARoomActor>(HitActor))
		{
			return FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Room,
				Room->DMRoom.Id, Room->DMRoom.Name);
		}
	}
	if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
		EInstrumentAvailableSelection::IAS_Wall))
	{
		if (const auto Wall = Cast<AWallActor>(HitActor))
		{
			return FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Wall,
				Wall->DMWall.Id, Wall->DMWall.Name);
		}
	}
	if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
		EInstrumentAvailableSelection::IAS_Furniture))
	{
		if (const auto Furniture = Cast<AFurniture>(HitActor))
		{
			return FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Furniture,
				Furniture->ID, Furniture->Data.Name.ToString());
		}
	}
	// else if TODO: add check for prop

	return FSceneObjectSelection();
}
