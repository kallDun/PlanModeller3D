#pragma once

#include "CoreMinimal.h"
#include "RunnableGenerationAlgorithm.h"
#include "Models/Furnitures/Generation/SelectedFurnitureData.h"


class SelectFurnitureGenerationAlgorithm : public RunnableGenerationAlgorithm
{
public:
	TArray<FSelectedFurnitureData> GeneratedFurniture;

	virtual void Generate() override;
};
