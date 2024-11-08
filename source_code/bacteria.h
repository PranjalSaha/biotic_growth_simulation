#include <vector>
#include <algorithm> // For std::remove
using std::vector, std::remove;



#ifndef BACTERIA_H
#define BACTERIA_H

// Forward declaration of the `activity` class
class activity;

class bacterium
{
		// Class to define the characteristics of the bacteria species
		// The growth of the bacteria depends on the environment it is in

	friend activity;

protected:
	
	int population_num = 10000;	// The number of bacteria in the environment
	
	float min_energy,			// Minimum energy a bacterium can have
		  max_energy,			// Maximum energy a bacterium can have
		  living_energy,		// The constant energy consumed by bacterium to 
								// live
		  reproduction_energy,	// Energy required by bacterium for reproduction
		  acidic_limit,			// The maximum amount of acetate concentration
								// a bacterium can handle in its proximity
		  proximity,			// What the bacterium defines as proximity
		  energy_per_nutrient,	// Energy bacterium gets per unit of nutrient
		  rate_of_consumption,	// max rate of consumption of energy
		  movement_speed;		// Speed in patches per refresh

	int position[2];		// The position of bacterium on axis (x, y)
	float energy;			// The energy of the bacterium
		
	bacterium(int const (&pos)[2], float const energy_lvl = 0)
	{
		position[0] = pos[0];
		position[1] = pos[1];
		energy = energy_lvl;
	}

public:
	bacterium() 
	{
		// Defaults all values of the bacterium to default values of the classes
		// of the storing values
	}
	bacterium(int /* parameters */);	// Constructor which sets the values of
										// the parameters to a certain value

	// Defining an equality operator for `remove` to work correctly
	bool operator==(const bacterium& other) const
	{
		return position[0] == other.position[0] &&
		       position[1] == other.position[1] &&
		       energy == other.energy;
	}
};


class cluster
{
protected:
	vector<bacterium> members;

public:
	void add(bacterium individual)
	{
		members.push_back(individual);
	}

	void omit(bacterium individual)
	{
		// Removes the first occurrence of `individual` from `members`
		members.erase(remove(members.begin(), members.end(),
					individual), members.end());
	}
};




#endif

