#include <cmath>
#include <stdexcept>
using namespace std;

#include "species.h"
#include "random.h"

float Bacterium::temporalResolution = 1.0f;


void Bacterium::setID(unsigned long int id)
{
	if ( bacteriaID !=0 )
	{
		throw runtime_error("Cannot modify value - Bacteria already registered");
		return;
	}

	if ( id == 0 )
	{
		throw invalid_argument("Cannot set bacteriaID to 0");
		return;
	}

	bacteriaID = id;
}


unsigned long int Bacterium::getID()
{
	return bacteriaID;
}


void Bacterium::updateTemporalResolution(float resolution) 
{
    if (resolution <= 0) 
    {
        throw std::invalid_argument("Temporal resolution must be a positive value.");
    }

    temporalResolution = resolution;
}


float Bacterium::getTemporalResolution() 
{
	return temporalResolution;
}


Bacterium::Bacterium()
{
	updateTemporalResolution( 1.0f );
}


Bacterium::Bacterium( const vector<int> pos, float const energy_lvl)
{
	position = pos;
	energy = energy_lvl;
}


bool Bacterium::operator==(const Bacterium& other) const
{
	return bacteriaID == other.bacteriaID;
}


void Bacterium::reproduce( Environment* surroundings , Bacterium& offspring)
{
	if (energy > reproductionEnergy)
	{
		// Creates an offspring and returns it
		offspring = Bacterium( position, energy / 2 );
		energy /= 2;
	}
	offspring = Bacterium();
}


void Bacterium::eat( Environment* surroundings )
{
    float total_nutrients_consumed = 0.0f;
    
    // Getting the current position of the Bacterium
    vector<int> size = surroundings->getSize();

    // Define the range of indices to check based on the proximity
	int start_x = std::max(0, static_cast<int>(position[0] - proximity));
    int end_x = std::min(size[0], static_cast<int>(position[0] + proximity));
    int start_y = std::max(0, static_cast<int>(position[1] - proximity));
    int end_y = std::min(size[1], static_cast<int>(position[1] + proximity));
    int start_z = std::max(0, static_cast<int>(position[2] - proximity));
    int end_z = std::min(size[2], static_cast<int>(position[2] + proximity));

    // Iterate through the defined range based on proximity
	// Start the 
	for (int p = 100; p > 0; p--)
     for (int i = start_x; i < end_x; ++i) 
	  for (int j = start_y; j < end_y; ++j)
	   for (int k = start_z; k < end_z; ++k) 
		{
			if (total_nutrients_consumed >= rateOfConsumption)
				break;

			float nutrient_lvl = surroundings->getNutrientLevel({i, j, k});
			if (nutrient_lvl <= 0.0f)
				continue;
			
			// checks wether the point is further from the proximity value
			float distance = sqrt ( pow(i - position[0], 2) 
								  + pow(j - position[1], 2)
								  + pow(k - position[2], 2) );
			if (distance > proximity / p )
				continue;

			
			// Calculate how much nutrient can be consumed
			float nutrient_to_consume = min(nutrient_lvl,
					 rateOfConsumption - total_nutrients_consumed);
			total_nutrients_consumed += nutrient_to_consume;

			// Update the nutrient present in the locale
			surroundings->updateNutrient( {i,j,k}, -nutrient_to_consume);
		}

	// Update the Bacterium's energy based on the total nutrients consumed
	energy += total_nutrients_consumed * energyPerNutrient;

}


void Bacterium::move( Environment* surroundings )
{
	RandomGenerator ranGen;
	const int range = movementSpeed;

	// Generate random offsets within the range for x and y
	int x_offset = ranGen.Int(-range, range);
	int y_offset = ranGen.Int(-range, range);

	// Update the Bacterium's position with the offsets
	position[0] += x_offset;
	position[1] += y_offset;

	// Define boundaries 
	const int max_x = 100;
	const int max_y = 100;

	// Apply reflection physics for the x-axis
	if (position[0] < 0) 
	{
		position[0] = -position[0]; 
				// Reflect back into bounds
	} 
	else if (position[0] > max_x) 
	{
		position[0] = max_x - (position[0] - max_x);
				// Reflect back
	}

				// Apply reflection physics for the y-axis
	if (position[1] < 0) 
	{
		position[1] = -position[1];
	}
	else if (position[1] > max_y) 
	{
		position[1] = max_y - (position[1] - max_y);
	}
}


void Bacterium::die()
{
	alive = 0;
}


void Bacterium::adapt( Environment* surroundings ){};


bool Bacterium::canLive( Environment* surroundings ) const
{
	if ( energy <= minEnergy )
		return 0;

	if ( surroundings -> getAcetateLevel( position ) > acidicLimit )
		return 0;

	else
		return 1;
}

bool Bacterium::isAlive() const
{
	return alive;
}



void Bacterium::live( Environment* surroundings, Bacterium& offspring)
{
	move( surroundings );
	eat( surroundings );
	adapt( surroundings );
	reproduce( surroundings, offspring );

	energy = energy - livingEnergy;
	if ( ! canLive( surroundings ) )
		die();
}
