//
//
//  This file calculates the VaR using the Montecarlo method for different
//  types of distributions. It consists in a first approximation to coding
//  in C++,
//
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
// calling our headers that contain user defined classes
#include "densities_1.h"
#include "MC.h"

//getting constant pi just to avoid calling another library for one thing 
double pi = 3.141592;

int main() {
    // defining number of simulations (in general has to be bigger or equal than this)
    int num_samples = 100000;
    
    // asking the user for the confidence interval
    double alpha;
    std::cout << "\nEnter confidence level (1-alpha): \n";
    std::cin >> alpha;

    // Initialising the parameters for the distributions
    // caveat here: we need to initialise them for every distribution

    double mu = 0.0;  
    double sigma = 0.2;  
    double alpha1 = 2.0;
    double xmin = 1.0;
    double nu = 5.0;

    // now the user decides the distribution type
    std::string dist_type;
    std::cout << "Enter distribution type (t, normal or pareto): ";
    std::cin  >> dist_type;

    //now we use the methods run() and show() of our Montecarlo class
    MC portfolio(num_samples, mu, sigma, alpha, alpha1, xmin, nu, dist_type);
    portfolio.run();
    portfolio.show();

    return 0;
}
