#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
using std::vector;

class Environment
{
	
protected:
	struct patch
	{
		float 
			nutrientLevel,			// amount of nutrient in a patch	
			acetateLevel;			// amount of acetate in a patch
	
		patch();
		
	};

	vector<vector<vector<patch>>> locale; // 3D distribution of patches
	vector<int> ranges; 

	float CO2Level = 0.0f;
	float temporalResolution = 1.0f;		  // units - seconds

public:
	
	// Initialiser
	Environment( int randomiseType = 0, vector<int> = {100,100,100},
				 float nutrientValue = 100.0f, float value = 100.0f, 
				 float tempres = 1.0f);

	
	// Mutators
	void updateNutrient(const vector<int>& location, float nutrientChange);
	void updateAcetate(const vector<int>& location, float acetateChange);
	void updateCO2(float CO2Increase);
	void updateTemporalResolution(const float tempresNew);
	
	
	// Accessors
	vector<int> getSize() const;				// returns size of Environment	
	float getNutrientLevel(const vector<int>& ) const;
	float getAcetateLevel(const vector<int>& ) const;
	float getCO2Level();
	float getTemporalResolution();
};

#endif
