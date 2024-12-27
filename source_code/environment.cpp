#include "environment.h"
#include <stdexcept>
#include "random.h"

Environment::patch::patch()
{
	nutrientLevel = 0;  // sets the default concentrations to 0
	acetateLevel = 0;
}


Environment::Environment(int randomiseType, vector<int> rangesValue,
						 float nutrientValue, float acetateValue, float tempres)
{
	// Validate ranges size
	if (rangesValue.size() != 3)
	{
		throw std::invalid_argument("Error: rangesValue must be a 3-element "
									"vector.");
	}

	ranges = rangesValue;

	// Initialize locale (3D grid of patches)
	locale.resize(ranges[0], std::vector<std::vector<patch>>(ranges[1],
						 std::vector<patch>(ranges[2])));

	RandomGenerator rangen;

	// Switch case for randomiseType
	switch (randomiseType)
	{
		case 0:
			// Set nutrient and acetate levels to the provided values (no randomization)
			for (int i = 0; i < ranges[0]; i++)
			 for (int j = 0; j < ranges[1]; j++)
			  for (int k = 0; k < ranges[2]; k++)
				{
					locale[i][j][k].nutrientLevel = nutrientValue;
					locale[i][j][k].acetateLevel = acetateValue;
				}
			break;

		case 1:
			// Randomize nutrient and acetate levels for each patch
			for (int i = 0; i < ranges[0]; i++)
			 for (int j = 0; j < ranges[1]; j++)
			  for (int k = 0; k < ranges[2]; k++)
				{
					locale[i][j][k].nutrientLevel =
						rangen.Float(0.0f, nutrientValue);
					locale[i][j][k].acetateLevel =
						rangen.Float(0.0f, acetateValue);
				}
			break;

		default:
			// Handle the case when randomiseType is not recognized
			throw std::invalid_argument("Error: Unknown randomiseType.");
	}

	temporalResolution = tempres;
}


void Environment::updateNutrient(const std::vector<int>& position,
								 float nutrientChange)
{
	// Ensure the position is within bounds
	int i = position[0], j = position[1], k = position[2];

	if (i >= 0 && i < ranges[0] && 
		j >= 0 && j < ranges[1] && 
		k >= 0 && k < ranges[2])
	{
		// Update the nutrient level at the specified position
		locale[i][j][k].nutrientLevel += nutrientChange;
	}
}

void Environment::updateAcetate(const std::vector<int>& position,
								float acetateChange)
{
	// Ensure the position is within bounds
	int i = position[0], j = position[1], k = position[2];

	if (i >= 0 && i < ranges[0] && 
		j >= 0 && j < ranges[1] && 
		k >= 0 && k < ranges[2])
	if (i >= 0 && i < ranges[0] && j >= 0 &&
		j < ranges[1] && k >= 0 && k < ranges[2])
	{
		// Update the acetate level at the specified position
		locale[i][j][k].acetateLevel += acetateChange;
	}
}

void Environment::updateCO2(float CO2Increase)
{
	CO2Level += CO2Increase;
}

void Environment::updateTemporalResolution(const float tempResNew)
{
	temporalResolution = tempResNew;
}

std::vector<int> Environment::getSize() const
{
	std::vector<int> range = {ranges[0], ranges[1], ranges[2]};
	return range;
}

float Environment::getNutrientLevel(const std::vector<int>& position) const
{
	// Returns the nutrient level at a specific position in the locale

	int i = position[0], j = position[1], k = position[2];

	// Ensure the position is within bounds
	if (i >= 0 && i < ranges[0] && 
		j >= 0 && j < ranges[1] && 
		k >= 0 && k < ranges[2])
	if (i >= 0 && i < ranges[0] && j >= 0 &&
		j < ranges[1] && k >= 0 && k < ranges[2])
	{
		return locale[i][j][k].nutrientLevel;  // Return the nutrient level
	}

	// Return a default value (-1.0) if the position is out of bounds
	return -1.0f;
}

float Environment::getAcetateLevel(const std::vector<int>& position) const
{
	// Returns the acetate level at a specific position in the locale

	int i = position[0], j = position[1], k = position[2];

	// Ensure the position is within bounds
	if (i >= 0 && i < ranges[0] && 
		j >= 0 && j < ranges[1] && 
		k >= 0 && k < ranges[2])
	if (i >= 0 && i < ranges[0] && j >= 0 &&
		j < ranges[1] && k >= 0 && k < ranges[2])
	{
		// Return the acetate concentration
		return locale[i][j][k].acetateLevel;
	}

	// Return a default value (-1.0) if the position is out of bounds
	return -1.0f;
}

float Environment::getCO2Level()
{
	return CO2Level;
}

float Environment::getTemporalResolution()
{
	return temporalResolution;
}

