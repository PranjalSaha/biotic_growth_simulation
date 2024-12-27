#ifndef CLUSTER_H
#define CLUSTER_H

#include "environment.h"
#include "species.h"
#include <string>
#include <vector>

class Cluster : public Environment, protected Bacterium
{

protected:
	// A vector of bacterium which contains all alive members
	vector<Bacterium> alive;
	// A vector of bacterium which contains all dead members
	vector<Bacterium> dead;

	// values containing total values of bacteria
	unsigned long int totalBacteria;
	unsigned long int totalAliveBacteria;
	unsigned long int totalDeadBacteria;
	
	// Accessors 
	std::pair<bool, unsigned long int> isPresent( Bacterium );
	
	// Mutators - functions to edit the members of the cluster
	// add - registers the bacterium into the cluster
	void add( Bacterium* );
	void omit( Bacterium* );

	void step();


public:

	// initializer
	Cluster(int numBacteria = 100, int randomiseType = 0, float EnergyLevel = 1);

	void updateTemporalResolution(float tempRes);

	// runs as long as all the bacteria does not die
	void run(const std::string filename);
	// runs uptil a particular time speciefied or until all bacteia die
	void run(const std::string filename, float time);	

	

};


#endif
