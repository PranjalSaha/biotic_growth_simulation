#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <string>
using namespace std;

#include "cluster.h"
#include "random.h"


Cluster::Cluster(int numBacteria, int randomiseType,double energyValue)
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
                double randomEnergy = ranGen.Double(0, energyValue);
                
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


    for (Bacterium& individual : alive)
    {
        aliveBefore = individual.isAlive();
        individual.live(static_cast<Environment*>(this), *offspring);

        if (offspring->isAlive() == 1)
        {
            newMembers.push_back(*offspring);
            offspring = new Bacterium();
        }

        if (aliveBefore && !individual.isAlive())
        {
            deadMembers.push_back(individual);
        }
    }


    for (Bacterium& individual : newMembers)
        add(&individual);
    for (Bacterium& individual : deadMembers)
        omit(&individual);

    delete offspring; // Clean up dynamically allocated memory
}

void Cluster::updateTemporalResolution(double newResolution)
{
    Environment::updateTemporalResolution(newResolution);
    Bacterium::updateTemporalResolution(newResolution);
}


void Cluster::run(string filename)
{
	filename = "../results/" + filename;
    ofstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("Could not open file for writing.");
    }

    file << "TimeElapsed,AliveBacteria,TotalBacteria,NetCO2," 
         << "TotalNutrient,TotalAcetate\n";

    unsigned long int timeStep = 0;
    double timeElapsed = 0.0f;
    double tempres = Bacterium::getTemporalResolution();

    const unsigned long int writingFrequency = 1; 
            // Set the number of iterations to 1000
    unsigned long int iterationCounter = 0; // To track the number of iterations

    cout << "\033[2J"; // Clear the screen once before starting

    while (totalAliveBacteria > 0)
    {
        step(); // Perform one step, updating bacteria and environment
        timeStep++;
        timeElapsed = timeStep * tempres;
        
        // Collect data
        double currentCO2 = getCO2Level();
        double currentNutrient = getNutrientLevel();
        double currentAcetate = getAcetateLevel();

        // Write to file
        file << timeElapsed << ","
             << totalAliveBacteria << ","
             << totalBacteria << ","
             << currentCO2 << ","
             << currentNutrient << ","
             << currentAcetate << "\n";

        iterationCounter++;

        // Print every writingFrequency iterations
        if (iterationCounter >= writingFrequency)
        {
            // Reset the iteration counter
            iterationCounter = 0;

   
            // Move the cursor to the top-left corner (0, 0)
            cout << "\033[H";

            // Display the updated simulation data
            cout << "Simulation Data:\n";
            cout << "================\n";
            cout << fixed << setprecision(2);
            cout << "Time Elapsed   : " << timeElapsed << " seconds"
                      << "                \n";
            cout << "Alive Bacteria : " << totalAliveBacteria
                      << "                \n";
            cout << "Total Bacteria : " << totalBacteria 
                      << "                \n";
            cout << "Net CO2 Level  : " << currentCO2 
                      << "                \n";
            cout << "Total Nutrient : " << currentNutrient 
                      << "                \n";
            cout << "Total Acetate  : " << currentAcetate 
                      << "                \n";
            cout << "Dead Bacteria  : " << totalDeadBacteria
                      << "                \n";

            cout << flush; // Ensure output is written immediately
        }
    }

    file.close();
}


void Cluster::run(string filename, double maxTime)
{
	filename = "../results/" + filename;
    ofstream file(filename);
	cout << filename << endl;
    
    if (!file.is_open())
    {
        throw runtime_error("Could not open file for writing.");
    }

    // Write the CSV header
    file << "TimeElapsed,AliveBacteria,TotalBacteria,";
    file << "NetCO2,TotalNutrient,TotalAcetate\n";

    unsigned long int timeStep = 0;
    double timeElapsed = 0.0f;
    double tempres = Bacterium::getTemporalResolution();

    // file will be written every writingFrequency interations
    // to track the number of iterations iteration counter will be used
    const unsigned long int writingFrequency = 1;
    unsigned long int iterationCounter = 0;
            
    cout << "\033[2J"; // Clear the screen once before starting
    
    while (totalAliveBacteria > 0 && timeElapsed < maxTime)
    {
        step(); // Perform one simulation step
        timeStep++;
        timeElapsed = timeStep * tempres;
        
        // Collect data
        double currentCO2 = getCO2Level();
        double currentNutrient = getNutrientLevel();
        double currentAcetate = getAcetateLevel();

        // Write data to the file
        file << timeElapsed << ","
             << totalAliveBacteria << ","
             << totalBacteria << ","
             << currentCO2 << ","
             << currentNutrient << ","
             << currentAcetate << "\n";

        // Check if it's time to update the display
        iterationCounter++;

        // Print every writingFrequency iterations
        if (iterationCounter >= writingFrequency)
        {
            // Reset the iteration counter
            iterationCounter = 0;

            // Move the cursor to the top-left corner (0, 0)
            cout << "\033[H";

            // Display the updated simulation data
            cout << "Simulation Data:\n";
            cout << "================\n";
            cout << fixed << setprecision(2);
            cout << "Time Elapsed   : " << timeElapsed << " seconds"
                      << "                \n";
            cout << "Alive Bacteria : " << totalAliveBacteria
                      << "                \n";
            cout << "Total Bacteria : " << totalBacteria 
                      << "                \n";
            cout << "Net CO2 Level  : " << currentCO2 
                      << "                \n";
            cout << "Total Nutrient : " << currentNutrient 
                      << "                \n";
            cout << "Total Acetate  : " << currentAcetate 
                      << "                \n";

            cout << flush; // Ensure output is written immediately
        }
    }

    file.close();
}

