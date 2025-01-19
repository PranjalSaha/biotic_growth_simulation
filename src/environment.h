#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
using std::vector;

class Environment
{
    
protected:
    struct patch
    {
        double 
            nutrientLevel = 0,          // amount of nutrient in a patch    
            acetateLevel = 0;           // amount of acetate in a patch
    
        patch();
        
    };

    vector<vector<vector<patch>>> locale; // 3D distribution of patches
    vector<int> ranges; 

    double CO2Level = 0.0f;
    long double totalNutrientLevel = 0.0f; 
    long double totalAcetateLevel = 0.0f;
    double temporalResolution = 1.0f;         // units - seconds
    

public:
    
    // Initialiser
    Environment( int randomiseType = 0, vector<int> = {50,50,50},
                 double nutrientValue = 1.0f, double acetateValue = 0.0f, 
                 double tempres = 1.0f);

    
    // Mutators
    void updateNutrient(const vector<int>& location, double nutrientChange);
    void updateAcetate(const vector<int>& location, double acetateChange);
    void updateCO2(double CO2Increase);
    void updateTemporalResolution(const double tempresNew);
    
    
    // Accessors
    vector<int> getSize() const;                // returns size of Environment  
    double getNutrientLevel(const vector<int>& ) const; // nutrient level of patch
    double getNutrientLevel() const;        // nutrient level of entire environment                 
    double getAcetateLevel(const vector<int>& ) const; // nutrient level of patch
    double getAcetateLevel() const;     // nutrient level of whole environment
    double getCO2Level();
    double getTemporalResolution();
};

#endif
