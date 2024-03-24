#pragma once

UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EInstrumentInputType : uint8
{
	None = 0,
	TriggerExitInput = 1 << 0,
	TriggerUseInput	= 1 << 1,
	TriggerPreviewInput	= 1 << 2,
	TwoAxisInput = 1 << 3,
	OneAxisInput = 1 << 4,
	TriggerNextInput = 1 << 5,
	TriggerPreviousInput = 1 << 6,
	TriggerUndoInput = 1 << 7,
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
