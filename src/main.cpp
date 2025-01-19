#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "cluster.h"
using namespace std;

int main()
{
	Cluster cottonBed(100);

	cottonBed.run("samplefile.csv", 1000.0f);
}
