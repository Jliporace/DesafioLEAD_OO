#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


class Filter
{
    private:
        std::vector <float> timestamp;
	    std::vector <float> data;
		std::fstream file;

    public:
        void modulation (int rate);
        void movingAverage(int numSamples);
        void lowPassFilter(float tau, float period);
        Filter(const std::vector<float>& timestamp, const std::vector<float>& data);
		bool openFile(std::string path);

};