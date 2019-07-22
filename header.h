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
		fstream file;

    public:
        void modulation (int rate);
        void movingAverage(int numSamples);
        void lowPassFilter(float tau, float period);
        Filter(const vector<float>& timestamp, const vector<float>& data);
		bool openFile(string path);

};