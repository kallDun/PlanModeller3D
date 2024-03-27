#include "Managers/Furnitures/Generation/Components/Algorithms/SelectFurnitureGenerationAlgorithm.h"


void SelectFurnitureGenerationAlgorithm::Generate()
{
	GeneratedFurniture = {};
	// Do the generation here

	// Need to check if the algorithm was stopped
	if (Status == ERunnableStatus::Stopped)
	{
		OnGenerationFinished.ExecuteIfBound(Status);
		return;
	}

	Status = ERunnableStatus::Finished;
	OnGenerationFinished.ExecuteIfBound(Status);
}
