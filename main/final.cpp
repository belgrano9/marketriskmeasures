//
//
//  This file calculates the VaR using the Montecarlo method for a normal
// distribution with historical data.
//  
//
//


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

// we include the header to read the .csv
#include "densities_1.h"
#include "MC.h"
#include "read.h"

double pi = 3.141592;

int main() {

    // Read data from CSV file
    Stock stock("C:/Users/tomso/Desktop/QEM/2nd year/C++/^SSMI V2.csv");
    // compute returns
    auto returns = stock.computeReturns();
    // compute mean
    double mean = stock.computeMean(returns);
    // compute variance
    double variance = stock.computeVariance(returns, mean);

    double stddev = sqrt(variance);

    int num_samples = 100000;

    double alpha;
    std::cout << "\nEnter confidence level (1-alpha): \n";
    std::cin >> alpha;

    std::string dist_type;
    std::cout << "Enter distribution type (if we do not use normal the program we will use predetermined values for the other distributions): ";
    std::cin  >> dist_type;

    double alpha1 = 2.0;
    double xmin = 1.0;
    double nu = 5.0;

    MC portfolio(num_samples, mean, stddev, alpha, alpha1, xmin, nu, dist_type);
    portfolio.run();
    portfolio.show();

    return 0;
}