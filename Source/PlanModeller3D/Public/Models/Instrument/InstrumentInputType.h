#pragma once

UENUM(BlueprintType, meta=(Bitflags))
enum class EInstrumentInputType : uint8
{
	None					UMETA(Hidden),			
	TriggerExitInput		UMETA(DisplayName = "Trigger Exit"),
	TriggerUseInput			UMETA(DisplayName = "Trigger Use"),
	TriggerPreviewInput		UMETA(DisplayName = "Trigger Preview"),
	TwoAxisInput			UMETA(DisplayName = "Two Axis"),
	OneAxisInput			UMETA(DisplayName = "One Axis"),
	TriggerNextInput		UMETA(DisplayName = "Trigger Next"),
	TriggerPreviousInput	UMETA(DisplayName = "Trigger Previous"),
	TriggerUndoInput		UMETA(DisplayName = "Trigger Undo"),
};
ENUM_CLASS_FLAGS(EInstrumentInputType)


static bool Contains(const EInstrumentInputType Flags, const EInstrumentInputType Flag)
{
	return (Flags & Flag) == Flag;
}

static void Add(EInstrumentInputType& Flags, const EInstrumentInputType Flag)
{
	Flags |= Flag;
}

static void Remove(EInstrumentInputType& Flags, const EInstrumentInputType Flag)
{
	Flags &= ~Flag;
}
