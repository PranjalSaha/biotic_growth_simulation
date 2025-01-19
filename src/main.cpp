#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "cluster.h"
using namespace std;

int main()
{
    Cluster cottonBed(100);                // initial number of bacteria

	string filename;
	cout << "Enter filename : ";
	cin >> filename;

    cottonBed.run(filename, 1000.0f); // inputs - 
										   // name of output file
										   // max time for running simulation
}
