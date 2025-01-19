#include <cmath>
#include <stdexcept>
#include <iostream>         // remove
#include <iomanip>
using namespace std;

#include "species.h"
#include "random.h"

double Bacterium::temporalResolution = 1.0f;


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


void Bacterium::updateTemporalResolution(double resolution) 
{
    if (resolution <= 0) 
    {
        throw invalid_argument("Temporal resolution must be a positive value.");
    }

    temporalResolution = resolution;
}


double Bacterium::getTemporalResolution() 
{
    return temporalResolution;
}


double Bacterium::getAcetateNearby(Environment* env) const
{
    /*
     * Calculate the total nutrients in the proximity of the bacterium.
     * Args:
     *     Pointer to the environment the bacterium exists in.
     * Returns:
     *     Double value of net nutrient level in the proximity
     */

    double totalAcetate = 0.0f;
    const vector<int> size = env->getSize();
    
    // Iterate over the 3D grid within the proximity bounding box
    for (int x = max(0, position[0] - (int)proximity);
         x <= min(size[0] - 1, position[0] + (int)proximity); ++x)
      for (int y = max(0, position[1] - (int)proximity);
           y <= min(size[1] - 1, position[1] + (int)proximity); ++y)
        for (int z = max(0, position[2] - (int)proximity);
             z <= min(size[2] - 1, position[2] + (int)proximity); ++z)
        {
            // Calculate Euclidean distance
            double distance = sqrt((x - position[0]) * (x - position[0])
                                 + (y - position[1]) * (y - position[1])
                                 + (z - position[2]) * (z - position[2]));

            // Check if the patch is within proximity
            if (distance <= proximity)
                totalAcetate += env->getAcetateLevel({x, y, z});
        }

    return totalAcetate;
}


Bacterium::Bacterium()
{
    updateTemporalResolution( 1.0f );
}


Bacterium::Bacterium( const vector<int> pos, double const energy_lvl)
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
    else
        offspring = Bacterium();
}


void Bacterium::eat( Environment* surroundings )
{
    double totalNutrientsConsumed = 0.0f;
    
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
            if (totalNutrientsConsumed >= rateOfConsumption)
                break;

            double nutrient_lvl = surroundings->getNutrientLevel({i, j, k});
            if (nutrient_lvl <= 0.0f)
                continue;
            
            // checks wether the point is further from the proximity value
            double distance = sqrt ( pow(i - position[0], 2) 
                                  + pow(j - position[1], 2)
                                  + pow(k - position[2], 2) );
            if (distance > proximity / p )
                continue;

            
            // Calculate how much nutrient can be consumed
            double nutrient_to_consume = min(nutrient_lvl,
                     rateOfConsumption - totalNutrientsConsumed);
            totalNutrientsConsumed += nutrient_to_consume;

            // Update the nutrient present in the locale
            surroundings->updateNutrient( {i,j,k}, -nutrient_to_consume);
        }

    // Update the Bacterium's energy based on the total nutrients consumed
    energy += totalNutrientsConsumed * energyPerNutrient;
}


void Bacterium::move(Environment* surroundings)
{
    RandomGenerator ranGen;
    const int range = movementSpeed;

    // Generate random offsets within the range for x, y, and z
    int x_offset = ranGen.Int(-range, range);
    int y_offset = ranGen.Int(-range, range);
    int z_offset = ranGen.Int(-range, range);

    // Update the Bacterium's position with the offsets
    position[0] += x_offset;
    position[1] += y_offset;
    position[2] += z_offset;

    // Define boundaries for x, y, and z axes
    const int max_x = 100;
    const int max_y = 100;
    const int max_z = 100;

    // Apply reflection physics for the x-axis
    if (position[0] < 0)
    {
        position[0] = -position[0]; // Reflect back into bounds
    }
    else if (position[0] > max_x)
    {
        position[0] = max_x - (position[0] - max_x); // Reflect back
    }

    // Apply reflection physics for the y-axis
    if (position[1] < 0)
    {
        position[1] = -position[1]; // Reflect back into bounds
    }
    else if (position[1] > max_y)
    {
        position[1] = max_y - (position[1] - max_y); // Reflect back
    }

    // Apply reflection physics for the z-axis
    if (position[2] < 0)
    {
        position[2] = -position[2]; // Reflect back into bounds
    }
    else if (position[2] > max_z)
    {
        position[2] = max_z - (position[2] - max_z); // Reflect back
    }
}


void Bacterium::die()
{
    alive = 0;
}


void Bacterium::adapt( Environment* surroundings ){};

double Bacterium::getEnergy()
{
    return energy;
}



bool Bacterium::canLive( Environment* surroundings ) const
{
    if ( energy <= minEnergy )
        return 0;

    if ( getAcetateNearby(surroundings) > acidicLimit )
        return 0;

    else
        return 1;
}


bool Bacterium::isAlive() const
{
    return alive;
}


void Bacterium::live(Environment* surroundings, Bacterium& offspring)
{
    move(surroundings);
    eat(surroundings);
    adapt(surroundings);
    reproduce(surroundings, offspring);
    
    energy = energy - livingEnergy; 
    surroundings->updateCO2(livingEnergy * CO2PerEnergy);

    if (!canLive(surroundings))
    {
        die();
    }
}

