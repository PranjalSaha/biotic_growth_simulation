#include "bacteria.h"
#include "environment.h"
#include "random.h"
#include <vector>
#include <cmath>
using std::vector, std::sqrt, std::min, std::pow, std::max;


#ifndef ACTIVITY_H 
#define ACTIVITY_H

class activity
{
	bacterium* individual;
	cluster* colony;

public:
	activity(bacterium* bacteria_input, cluster* colony_input)
	{
		individual = bacteria_input;
		colony = colony_input;
	}
	
	void reproduce()
	{
		if (individual->energy > individual->max_energy)
		{
			// Creates an offspring and adds it to the colony
			bacterium offspring(individual->position, individual->energy / 2);
			individual->energy /= 2;
			colony->add(offspring);
		}
	}

	void eat(bacterium& individual, environment& surroundings) 
	{
		float total_nutrients_consumed = 0.0f;
		
		int proximity = (int)individual.proximity;
		int size[2] = { surroundings.range_x, surroundings.range_y };
		int position[2] = { individual.position[0], individual.position[1] };

		// Define the range of indices to check based on the proximity
		int start_x = max(0, position[0] - proximity);
		int end_x = min(size[0] - 1, position[0] + proximity);
		int start_y = (0, position[1] - proximity);
		int end_y = min(size[1] - 1, position[1] + proximity);

		// Iterate through the defined range based on proximity
		for (int i = start_x; i <= end_x; ++i) 
		{
			for (int j = start_y; j <= end_y; ++j) 
			{
				environment::patch &active_patch = surroundings[i][j];
				// Check if we have reached the maximum consumption rate
				// Exit both loops if we have reached max consumption rate
				if (total_nutrients_consumed >= max_consumption_rate)
				{
					i = end_x + 1;
					break;
				}

				// Check if the nutrient in the active_patch is available
				// If no nutrient is available, skip this patch
				if (active_patch.nutrient_lvl == 0.0f) 
					break;

				// Calculate the distance to the nutrient active_patch using the
				// Euclidean distance formula
				float distance = sqrt ( pow( active_patch.position[0] - 
							position[0],2) + pow(active_patch.position[1] - 
								position[1], 2));

				// If nutrient is available and within the specified proximity
				if (distance > proximity) 
					break;		
				// Nutrient patch is too far
				
				// Determine how much nutrient can be consumed from this patch
				float nutrient_to_consume = min(active_patch.nutrient, 
						max_consumption_rate - total_nutrients_consumed);
			
				// Consume the nutrient from the patch
				total_nutrients_consumed += nutrient_to_consume;
			
				// Update the nutrient patch by subtracting the consumed nutrients
				active_patch.nutrient -= nutrient_to_consume;
			}
		}

		// Update individual energy based on the total nutrients consumed
		individual->energy += total_nutrients_consumed * individual->energy_per_nutrient;
	}
	
	void move()
	{
		RandomGenerator random;
		const int range = individual -> movement_speed;

		// Generate random offsets within the range for x and y
		int x_offset = random.Int(-range, range);
		int y_offset = random.Int(-range, range);

		// Update the bacterium's position with the offsets
		individual->position[0] += x_offset;
		individual->position[1] += y_offset;

		// Define boundaries 
		const int max_x = 100;
		const int max_y = 100;

		// Apply reflection physics for the x-axis
		if (individual->position[0] < 0) 
		{
			individual->position[0] = -individual->position[0]; 
					// Reflect back into bounds
		} else if (individual->position[0] > max_x) {
			individual->position[0] = max_x - (individual->position[0] - max_x);
					// Reflect back
		}

					// Apply reflection physics for the y-axis
		if (individual->position[1] < 0) {
			individual->position[1] = -individual->position[1];
		} else if (individual->position[1] > max_y) {
			individual->position[1] = max_y - (individual->position[1] - max_y);
		}
	}
	
	void die()
	{
		// Removes the individual from the colony if its energy is below minimum
		if (individual->energy < individual->min_energy)
			colony->omit(*individual);
	}
};


#endif
