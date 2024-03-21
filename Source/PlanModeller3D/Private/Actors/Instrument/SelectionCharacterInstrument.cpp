// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Instrument/SelectionCharacterInstrument.h"
#include "Actors/Character/PMCharacter.h"
#include "Managers/Instrument/ActorSelectable.h"
#include "Managers/Instrument/SelectionConverterLib.h"
#include "Models/Instrument/InstrumentAvailableSelection.h"
#include "Models/Instrument/InstrumentInputData.h"
#include "Models/Instrument/SceneObjectSelection.h"
#include "Services/Shared/Models/LinetraceRay.h"


void ASelectionCharacterInstrument::Input_Implementation(FInstrumentInputData InputData)
{
	Super::Input_Implementation(InputData);
	
	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerUseInput)
		&& InputData.UseInput)
	{
		SelectedSceneObject = USelectionConverterLib::ConvertToSelectionFromActor(GetHitActorFromLinetrace(), AvailableSelections);
		OnInstrumentUsed.Broadcast();
	}

	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerPreviewInput)
		&& InputData.PreviewInput)
	{
		if (PreviewedActor && PreviewedActor->GetClass()->ImplementsInterface(UActorSelectable::StaticClass()))
		{
			const auto PoolObject = Cast<IActorSelectable>(PreviewedActor);
			PoolObject->Execute_HideSelectionPreview(PreviewedActor);
		}
	
		PreviewedActor = GetHitActorFromLinetrace();
		PreviewedSceneObject = USelectionConverterLib::ConvertToSelectionFromActor(PreviewedActor, AvailableSelections);

		if (PreviewedSceneObject.SelectionType == EInstrumentAvailableSelection::IAS_None)
		{
			PreviewedActor = nullptr;
		}

		if (PreviewedActor && PreviewedActor->GetClass()->ImplementsInterface(UActorSelectable::StaticClass()))
		{
			const auto PoolObject = Cast<IActorSelectable>(PreviewedActor);
			PoolObject->Execute_ShowSelectionPreview(PreviewedActor);
		}
	}
}

void ASelectionCharacterInstrument::Deactivate()
{
	Super::Deactivate();
	
	if (PreviewedActor && PreviewedActor->GetClass()->ImplementsInterface(UActorSelectable::StaticClass()))
	{
		const auto PoolObject = Cast<IActorSelectable>(PreviewedActor);
		PoolObject->Execute_HideSelectionPreview(PreviewedActor);
	}
	PreviewedActor = nullptr;
}

AActor* ASelectionCharacterInstrument::GetHitActorFromLinetrace() const
{
	// make linetrace, get hit actor, check if it's a valid selection, if it is, set it as current selection
	// if it's not a valid selection, do nothing
	auto [Start, End] = Character->GetInstrumentLinetraceRay();
	auto Hit = FHitResult(ForceInit);
	auto Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Character);
	Params.bTraceComplex = true;

	if (bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		/*DrawDebugLine(GetWorld(),Start,Hit.Location,
			FColor(255, 0, 0),false, -1, 0,12.333);*/
		
		if (auto HitActor = Hit.GetActor())
		{
			return HitActor;
		}
	}
	return nullptr;
}
