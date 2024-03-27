#pragma once

UENUM(BlueprintType)
enum class ERunnableStatus : uint8
{
	NotStarted,
	Running,
	Stopped,
	Finished,
	Failed
};
