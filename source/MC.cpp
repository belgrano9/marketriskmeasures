//
//
//
//          MC.cpp
//
//
//
//

#include <random>
#include <iostream>
#include <cmath>
#include "MC.h"
#include "densities_1.h"

MC::MC(int num_samples_,double mu_,double sigma_,double alpha_,double alpha1_,double xmin_, double nu_, std::string dist_type_):
    //  initialising variables
    num_samples(num_samples_),
    mu(mu_),
    sigma(sigma_),
    alpha(alpha_),
    alpha1(alpha1_),
    xmin(xmin_),
    nu(nu_),
    dist_type(dist_type_)
{
}
    // this method simulates a return given that the distribution matches some user choice
    // and adds it to a vector of returns
    void MC::run() {
        if (dist_type == "t") {
            dist t_dist(nu, 1.0, dist::student);
            for (int i = 0; i < num_samples; i++) {
                double r = t_dist.compute();
                returns.push_back(r); 
            }
        }
        else if (dist_type == "normal") {
            dist normal_dist(mu, sigma, dist::normal);
            for (int i = 0; i < num_samples; i++) {
                double r = normal_dist.compute();
                returns.push_back(r);
            }
        }
        else if (dist_type == "pareto"){
            dist pareto_dist(xmin, alpha1, dist::normal);
            for (int i = 0; i < num_samples; i++) {
                double r = pareto_dist.compute();
                returns.push_back(r);
            }
        }
        else {
            std::cout << "Invalid distribution type. Please choose 't', 'normal' or 'pareto': " << std::endl;
            return;
        }
    }

    double MC::calculateVaR() {
        std::sort(returns.begin(), returns.end()); // sorting in ascending order
        int index = (int) (num_samples * (1 - alpha)); // getting the index
        return returns[index];
    }

    double MC::calculateES() {
        std::sort(returns.begin(), returns.end());
        int index = (int) (num_samples * (1 - alpha));
        double VaR = returns[index];
        // once that we get the VaR we need the expected value above the VaR.
        double sum = 0;
        int count = 0;
        for (int i = 0; i < index; i++) {
            if (returns[i] < VaR) {
                sum += returns[i];
                count++;
        }
    }
    return sum / count;
}

    // method to show results
    void MC::show() {
        double VaR = calculateVaR();
        std::cout << "Value at Risk (VaR) at " << (1 - alpha) * 100 << "%: " << VaR << std::endl;
        double ES = calculateES();
        std::cout << "Expected Shortfall at " << (1 - alpha) * 100 << "%: " << ES << std::endl;
    }

    //}
