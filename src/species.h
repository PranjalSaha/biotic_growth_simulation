#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include "environment.h"
using std::vector, std::min, std::max;


class Bacterium
{
		// Class to define the characteristics of the bacteria species
		// The growth of the bacteria depends on the Environment it is in

private:
	// unique value to identify a bacteria
	// as long as the bacteria value is 0, the bacteria is not registered
	// when the bacteria is registered, the value changes from 0 to another
	// value and cannot be changed again
	unsigned long int bacteriaID = 0;

protected:

	static double temporalResolution;			// unit - seconds
	

	// Value indicating wether bacteria is alive or dead
	bool alive = 1;
	
	// The biological specifications of the bacteria
	double 
		// Minimum energy a Bacterium can have ::
			minEnergy = 0,
		// Maximum energy a Bacterium can have ::
			maxEnergy = 500.0f,
		// The constant energy consumed by bacteria to live ::
			livingEnergy = 13.0f,
		// Energy required by Bacterium for reproduction ::
			reproductionEnergy = 300.0f,
		// Maximum amount of acetate concentration a bacterium can handle ::
			acidicLimit = 5.0f,
		// What the bacterium defines as proximity ::
			proximity = 3.0f,
		// Energy Bacterium gets per unit of nutrient ::
			energyPerNutrient = 10.0f,	
		// CO2 released per unit energy consumption
			CO2PerEnergy = 10.0f,
		// max rate of consumption of energy ::
			rateOfConsumption = 1.0f,
		// speed in micrometers per second ::
			movementSpeed = 1.0f;

	vector<int> position = {0,0,0};
	double energy = 0.0f;				// The energy of the Bacterium
	
	double getAcetateNearby(Environment* surroundings) const;
	

public:
	Bacterium();
	Bacterium(const vector<int> , double const energy_lvl = 10.0f);
										// the parameters to a certain value
	
	// function to update the value of the bacteriaID if applicable
	void setID(unsigned long int);
	unsigned long int getID();

	
	// activities (mutator functions) 
	void move( Environment* );
	void eat( Environment* );
	void reproduce( Environment* , Bacterium& );
	void live( Environment* , Bacterium& );
	void die();
	void adapt( Environment* );
	static void updateTemporalResolution(const double tempresNew);

	// ACCESSORS
	double getEnergy();
	// function to check wether the bacteria satisfies the conditions to live
	bool canLive( Environment* ) const;
	// checks wether the bacteria is alive
	bool isAlive() const;
	static double getTemporalResolution();

	// Defining an equality operator for `remove` to work correctly
	bool operator==(const Bacterium&) const;
};


#endif
