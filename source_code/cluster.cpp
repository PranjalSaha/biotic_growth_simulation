#include <iostream>
#include <fstream>
#include <stdexcept>
#include "cluster.h"
#include "random.h"
using namespace std;


Cluster::Cluster(int numBacteria, int randomiseType, float energyValue)
{
    RandomGenerator ranGen;


    // Initialize each bacterium
        // Randomize positions based on randomiseType
	switch (randomiseType)
	{
		case 1:
		
			for (int i = 0; i < numBacteria; ++i)
			{
				vector<int> randomPosition = { ranGen.Int(0, ranges[0]), 
											   ranGen.Int(0, ranges[1]), 
											   ranGen.Int(0, ranges[2]) };
				
				// Random energy value between 0 and energyValue
				float randomEnergy = ranGen.Float(0, energyValue);
				
				// Create the bacterium with the random position and energy
				Bacterium* individual = new Bacterium(randomPosition, randomEnergy);
				add( individual );
			}

		default:
			break;
    }
}


pair<bool, unsigned long int> Cluster::isPresent(Bacterium individual)
{
    for (unsigned long int i = 0; i < alive.size(); i++)
        if (alive[i] == individual)
            return {true, i};
    return {false, 0};
}


void Cluster::add(Bacterium* individual)
{
    totalBacteria++;
    totalAliveBacteria++;

	if ( individual->getID() == 0 )
		individual->setID( totalBacteria );
	else 
		cout << "Warning : stray bacteria added to cluster" << endl;
    alive.push_back( *individual );
}

void Cluster::omit(Bacterium* individual)
{
    pair<bool, unsigned long int> isPresentValue = isPresent(*individual);

    if (!isPresentValue.first)
    {
        throw runtime_error("Value not found in the vector");
    }
    else
    {
        dead.push_back(alive[isPresentValue.second]);
        totalDeadBacteria++;
        alive.erase(alive.begin() + isPresentValue.second);
        totalAliveBacteria--;
    }
}

void Cluster::step()
{
    Bacterium* offspring = new Bacterium();
    vector<Bacterium> newMembers;
    vector<Bacterium> deadMembers;
    bool aliveBefore;

    for (Bacterium individual : alive)
    {
        if (offspring->getID() != 0)
        {
            newMembers.push_back(*offspring);
            offspring = new Bacterium();
        }

        aliveBefore = individual.isAlive();
        individual.live(static_cast<Environment*>(this), *offspring);

        if (aliveBefore && !individual.isAlive())
            deadMembers.push_back(individual);
    }

    for (Bacterium individual : newMembers)
        add(&individual);
    for (Bacterium individual : deadMembers)
        omit(&individual);

    delete offspring; // Clean up dynamically allocated memory
}

void Cluster::updateTemporalResolution(float newResolution)
{
	Environment::updateTemporalResolution(newResolution);
    Bacterium::updateTemporalResolution(newResolution);
}

void Cluster::run(const string filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("Could not open file for writing.");
    }

    // Write the CSV header
    file << "TimeElapsed,AliveBacteria,TotalBacteria,NetCO2\n";

    unsigned long int timeStep = 0;
    float timeElapsed = 0.0f;
    float tempres = Bacterium::getTemporalResolution();

    while (totalAliveBacteria > 0)
    {
        step(); // Perform one step, updating bacteria and environment
        timeStep++;
        timeElapsed = timeStep * tempres;

        // Write data to the file
        file << timeElapsed << ","
             << totalAliveBacteria << ","
             << totalBacteria << ","
             << getCO2Level() << "\n";
    }

    file.close();
}

void Cluster::run(const string filename, float maxTime)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("Could not open file for writing.");
    }

    // Write the CSV header
    file << "TimeElapsed,AliveBacteria,TotalBacteria,NetCO2\n";

    unsigned long int timeStep = 0;
    float timeElapsed = 0.0f;
    float tempres = Bacterium::getTemporalResolution();

    while (totalAliveBacteria > 0 && timeElapsed < maxTime)
    {
        step();
        timeStep++;
        timeElapsed = timeStep * tempres;

        // Write data to the file
        file << timeElapsed << ","
             << totalAliveBacteria << ","
             << totalBacteria << ","
             << getCO2Level() << "\n";
    }

    file.close();
}

