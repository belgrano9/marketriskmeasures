//
//
//
//          densities_1.cpp
//          !!!!! this file will be the substitute of the sample() method of the pdf !!!!!! 
//
//
//


#include <random>
#include <iostream>
#include <cmath>
#include "densities_1.h"

// Generate random numbers from a pareto distribution
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);
std::normal_distribution<double> standard_normal(0.0, 1.0);

//initialise parameters
dist::dist(double param1_, double param2_, DisType TheDisType_):
    param1(param1_),
    param2(param2_),
    TheDisType(TheDisType_)
{
}

double dist::compute()
{
    // using switch to see different cases
    switch (TheDisType)
    {
        case normal:{ //using the brackets to avoid problems with variable definition
            double z = standard_normal(generator);
            return param1 + param2*z;}
        case pareto:{ // a future improvement will be to change this to generalized Pareto typpe IV 
            double u = distribution(generator);
            double x = param1 / pow(u, 1.0 / param2);
            return x;}
        case student:{
            std::chi_squared_distribution<double> chi_squared(param1);
            double v = standard_normal(generator);
            double t = v / sqrt(chi_squared(generator) / param1);
            return t;}
        default:    
            throw std::runtime_error("Unknown distribution type found.");
    }
    return 0;
}





