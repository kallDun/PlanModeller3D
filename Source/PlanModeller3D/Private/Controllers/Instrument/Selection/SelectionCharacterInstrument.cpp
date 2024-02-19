// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Instrument/Selection/SelectionCharacterInstrument.h"
#include "Actors/Foundation/RoomActor.h"
#include "Actors/Foundation/WallActor.h"
#include "Actors/Furnitures/Furniture.h"
#include "Components/StaticMeshComponent.h"


ASelectionCharacterInstrument::ASelectionCharacterInstrument()
{
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	LinetraceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LinetraceMesh"));
	RootComponent = RootMesh;
	LinetraceMesh->SetupAttachment(RootMesh);
}

void ASelectionCharacterInstrument::Use_Implementation()
{
	SelectedSceneObject = FSceneObjectSelection();
	
	// make linetrace, get hit actor, check if it's a valid selection, if it is, set it as current selection
	// if it's not a valid selection, do nothing
	
	auto Start = LinetraceMesh->GetComponentLocation();
	auto End = Start + (LinetraceMesh->GetForwardVector() * 1000);
	auto Hit = FHitResult(ForceInit);
	auto Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Character);
	Params.bTraceComplex = true;

	if (bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (auto HitActor = Hit.GetActor())
		{
			if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
				EInstrumentAvailableSelection::IAS_Room))
			{
				if (auto Room = Cast<ARoomActor>(HitActor))
				{
					SelectedSceneObject = FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Room, Room->DMRoom.Id);
				}
			}
			else if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
				EInstrumentAvailableSelection::IAS_Wall))
			{
				if (auto Wall = Cast<AWallActor>(HitActor))
				{
					SelectedSceneObject = FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Wall, Wall->DMWall.Id);
				}
			}
			else if (Contains(static_cast<EInstrumentAvailableSelection>(AvailableSelections),
				EInstrumentAvailableSelection::IAS_Furniture))
			{
				if (auto Furniture = Cast<AFurniture>(HitActor))
				{
					SelectedSceneObject = FSceneObjectSelection(EInstrumentAvailableSelection::IAS_Furniture, Furniture->ID);
				}
			}
			// else if TODO: add check for prop
		}
	}

	Super::Use_Implementation();
}
