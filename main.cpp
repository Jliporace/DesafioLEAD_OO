#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Filter.hpp"

using namespace std;

int main()
{
    vector <float> timestamp;
	vector <float> data;

	float fdata;
	float fcell;
	ifstream file;
	file.open("sensor.log");
	if (!file)
	{
    	cout << "Unable to open file sensor.log";
    	exit(1);   // call system to stop
	}
	while(file >> fcell >> fdata)
	{
		timestamp.push_back(fcell);
		data.push_back(fdata);
	}
	file.close();
    Filter filter(timestamp, data);
    filter.modulation(2);
    filter.movingAverage(20);
    filter.lowPassFilter(0.1,0.02);

    return 0;
}