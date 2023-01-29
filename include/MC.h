#ifndef MC_H
#define MC_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>


class MC
{
public:
    // Constructor takes all of this parameters plus the distribution type
    MC(int num_samples,double mu,double sigma,double alpha,double alpha1,double xmin, double nu, std::string dist_type);
    void run();
    double calculateVaR();
    double calculateES();
    void show();

private:
    // this variables should be private because once they are defined the user should not be able to access them again
    double mu;
    double sigma;
    int num_samples;
    double alpha;
    double alpha1;
    double xmin;
    double nu;
    std::string dist_type;
    std::vector<double> returns;
};


#endif
