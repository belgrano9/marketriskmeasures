//
//
//
//          read.cpp
//
//
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include "read.h"

Stock::Stock(std::string file_path_):
    file_path(file_path_)
{    
}

    std::vector<double> Stock::computeReturns() {
        // Read data from CSV file
        std::ifstream file(file_path);
        std::string line;

        // Store data in a vector
        std::vector<double> data;
        while (std::getline(file, line)) {
            // Extract closing price from line
            double closing_price;
            try {
                closing_price = std::stod(line.substr(line.find_last_of(",", line.find_last_of(",") - 1) + 1));
                data.push_back(closing_price);
            } catch (const std::invalid_argument& e) {
                // skip the line if the closing price is not a number like the first line in our data
                std::cerr << "Skipping invalid line: " << e.what() << std::endl;
            }
        }

        // Clean data (e.g. remove missing values)
        data.erase(std::remove(data.begin(), data.end(), 0), data.end());

        // Compute returns
        std::vector<double> returns;
        for (std::size_t i = 1; i < data.size(); ++i) {
            returns.push_back((data[i] - data[i - 1]) / data[i - 1]);
        }

        return returns;
    }

    double Stock::computeMean(std::vector<double> returns){
        // Compute mean of returns
        double sum = 0;
        for (auto &returns : returns) 
        {
            sum += returns;
        }

        double mean = sum / returns.size();
        std::cout << "Mean of Returns: " << mean << std::endl;
        return mean;
        
    } 
    double Stock::computeVariance(std::vector<double> returns, double mean){
        // Compute variance of returns
        double variance = 0;
        for (auto &returns : returns) 
        {
        variance += (returns - mean) * (returns - mean);
        }
    
        variance = variance / returns.size();
        std::cout << "Variance of Returns: " << variance << std::endl;
        return variance;
        
    
    } 
