#include <vector>
using std::vector;

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class activity;

class environment
{
	
	friend activity;

protected:
	struct patch
	{
		int nutrient_lvl;			// amount of nutrient in a patch	
		int acetate_conc;			// amount of acetate in a patch
		int pos[2];

		patch()
		{
			nutrient_lvl = 0;		// sets the default concentrations to 0
			acetate_conc = 0;
			
	   	}
		
		void updatepatch( int nutrient_change, int acetate_change )
		{							// function to change the concentrations
									// of nutrients and acetate
			nutrient_lvl += nutrient_change;
			acetate_conc += acetate_change;
		}
	};
	 int range_x, range_y;

public:
	
	environment(int x = 100, int y = 100 )
	{
		// Creates a 2D vector of patches
		// sets all values to 0 by default
		/*vector <vector <patch> > environment(y, vector<patch>(x));
		for ( int i; i < x; i++ )
			for ( int j; j < y; j++)
				pos = { i , j }		// Setting values of positions of vectors*/
			
		range_x = x;
		range_y = y;
	}

	int getsize()
	{ return range_x * range_y; }

};

#endif
