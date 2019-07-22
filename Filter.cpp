#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Filter.hpp"

using namespace std;


Filter::Filter(const vector<float>& timestamp, const vector<float>& data) :
	timestamp(timestamp), data(data)
{
}

bool Filter::openFile(string path)
{
	if (file.is_open())
	{
		file.close();
	}
	file.open(path, ios::out);
	if(file.is_open())
	{
		printf("Creating %20s file... \n", path.c_str());
	}
	else
	{
		printf("Couldn't open %20s file \n", path.c_str());
		return false;
	}
	return true;
}

void Filter::modulation(int rate)
    // Process the sensor data with a modulation of <rate> times. Creates and writes results in file modulation.log

{
	openFile("modulation.log");

	//The modulation of a vector is rate .* vector
	for (int i = 0; i<this->data.size(); i = i+1)
	{
		file << this->timestamp[i] << " " << this->data[i]*rate << endl;

	}
	file.close();
	return;
}

void Filter::movingAverage(int numSamples)
{
	openFile("mean.log");

	//Zeros addition to fullData in order to compute the first <numSamples> movingAverage
	vector <int> zerosV (numSamples,0);
	this->data.insert(data.begin(), zerosV.begin(), zerosV.end());

	//The movingAverage correspondent to the x[n] element is sum(x[n-numSamples]:x[n])/numSamples
	for (int i = numSamples; i<this->data.size(); i = i+1)
	{
		float sum = 0;
		for (int j = 0; j < numSamples; j++)
		{
			sum = sum + this->data[i - j];
		}
		float mean = sum/numSamples;
		file << this->timestamp[i-numSamples] << " " << mean << endl;

	}
	file.close();
    this->data.erase(data.begin(), data.begin()+numSamples);
	return;
}

void Filter::lowPassFilter(float tau, float period)
// Passes a low pass filter to the data with constant <tau> and sampling period <period>. Creates and writes results in file lowpass.log
{
	openFile("lowpass.log");

	//The low pass filter equation is y[k] = alpha*(u[k]+u[k+1]) - beta*y[k-1]
	float alpha = period/(2*tau + period);
	float beta = (period - 2*tau)/(period + 2*tau);
	float x = 0;
	for (int i = 0; i < this->data.size(); i = i +1)
	{
		x = alpha*(this->data[i] + this->data[i-1]) - beta*x;
		file << this->timestamp[i] << " " << x << endl;
	}
	file.close();
	return;
}