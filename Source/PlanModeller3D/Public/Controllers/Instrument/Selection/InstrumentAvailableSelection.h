#pragma once

UENUM(BlueprintType, meta = (Bitflags))
enum class EInstrumentAvailableSelection : uint8
{
	IAS_None			UMETA(DisplayName = "None"),
	IAS_Room			UMETA(DisplayName = "Room"),
	IAS_Wall			UMETA(DisplayName = "Wall"),
	IAS_Furniture		UMETA(DisplayName = "Furniture"),
	IAS_Prop			UMETA(DisplayName = "Prop"),
};
ENUM_CLASS_FLAGS(EInstrumentAvailableSelection)


static bool Contains(const EInstrumentAvailableSelection Flags, const EInstrumentAvailableSelection Flag)
{
	return (Flags & Flag) == Flag;
}

static void Add(EInstrumentAvailableSelection& Flags, const EInstrumentAvailableSelection Flag)
{
	Flags |= Flag;
}

static void Remove(EInstrumentAvailableSelection& Flags, const EInstrumentAvailableSelection Flag)
{
	Flags &= ~Flag;
}
