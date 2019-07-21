#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string> 

using namespace std; 

class Filter
{
    private:
        vector <float> timestamp;
	    vector <float> data;
    public: 
        void modulation (int rate);
        void movingAverage(int numSamples);
        void lowPassFilter(float tau, float period); 
        Filter(const vector<float>& timestamp, const vector<float>& data);
        
};

Filter::Filter(const vector<float>& timestamp, const vector<float>& data)
{
    this->timestamp = timestamp;
    this->data = data; 
}
void Filter::modulation(int rate)
    // Process the sensor data with a modulation of <rate> times. Creates and writes results in file modulation.log

{	
	fstream file;
	file.open("modulation.log", ios::out);
	if(file.is_open())
	{
		printf("Creating modulation.log file... \n");
	}
	else 
	{
		printf("Couldn't open modulation.log file \n");
		return;
	}
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
	fstream file;
	file.open("mean.log", ios::out);
	if(file.is_open())
	{
		printf("Creating mean.log file...\n ");
	}
	else 
	{
		printf("Couldn't open mean.log file \n");
		return;
	}
	//Zeros addition to fullData in order to compute the first <numSamples> movingAverage
	vector <int> zerosV (numSamples,0); 
	data.insert(data.begin(), zerosV.begin(), zerosV.end());
	
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
	return;
}

void Filter::lowPassFilter(float tau, float period)
// Passes a low pass filter to the data with constant <tau> and sampling period <period>. Creates and writes results in file lowpass.log
{
	fstream file;
	file.open("lowpass.log", ios::out);
	if(file.is_open())
	{
		printf("Creating lowpass.log file... \n");
	}
	else 
	{
		printf("Couldn't open lowpass.log file \n");
		return;
	}
	
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