#pragma once

#include "CoreMinimal.h"
#include "RunnableStatus.h"
#include "Managers/Furnitures/Generation/FurnitureGenerationComponent.h"


class RunnableGenerationAlgorithm : public FRunnable
{
	
public:
	ERunnableStatus Status;
	FGenerationAlgorithmDelegate OnGenerationFinished = FGenerationAlgorithmDelegate();

	virtual bool Init() override
	{
		Status = ERunnableStatus::NotStarted;
		return FRunnable::Init();
	}
	
	virtual uint32 Run() override
	{
		if (Status != ERunnableStatus::NotStarted) return 0;
		Generate();
		return 1;
	}
	
	virtual void Stop() override
	{
		FRunnable::Stop();
		Status = ERunnableStatus::Stopped;
	}

protected:
	virtual void Generate() = 0;
};
