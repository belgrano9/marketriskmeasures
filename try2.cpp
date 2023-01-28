#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include "densities_1.h"

double pi = 3.141592;


class MonteCarlo {
  private:
    int num_samples;
    double mu;
    double sigma;
    double alpha;

    double alpha1;
    double xmin;
    double nu;
    std::vector<double> returns;
    std::string dist_type; // new variable to store distribution type

  public:
    MonteCarlo(int num_samples, double mu, double sigma, double alpha, double alpha1, double xmin, double nu, std::string dist_type) {
        //  this may be used when there is an ambiguity between a data member and a member function argument
        this->num_samples = num_samples; 
        this->mu = mu;
        this->sigma = sigma;
        this->alpha = alpha;
        this->alpha1 = alpha1;
        this->xmin = xmin;
        this->nu = nu;
        this->dist_type = dist_type; // update variable value
    }


    void run() {
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

    double calculateVaR() {
        std::sort(returns.begin(), returns.end());
        int index = (int) (num_samples * (1 - alpha));
        return returns[index];
    }

    double calculateES() {
        std::sort(returns.begin(), returns.end());
        int index = (int) (num_samples * (1 - alpha));
        double VaR = returns[index];
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


    void show() {
        double VaR = calculateVaR();
        std::cout << "Value at Risk (VaR) at " << (1 - alpha) * 100 << "%: " << VaR << std::endl;
        double ES = calculateES();
        std::cout << "Expected Shortfall at " << (1 - alpha) * 100 << "%: " << ES << std::endl;
    }

    //}
};

int main() {
    int num_samples = 100000;
    
    double alpha;
    std::cout << "\nEnter confidence level (1-alpha): \n";
    std::cin >> alpha;

    // I should clean this part 
    double mu = 0.05;  // expected return
    double sigma = 0.2;  // volatility
    double alpha1 = 2.0;
    double xmin = 1.0;
    double nu = 5.0;

    // this part is fine
    std::string dist_type;
    std::cout << "Enter distribution type (t, normal or pareto): ";
    std::cin  >> dist_type;

    //this part is fine; we use the methods run() and show()
    MonteCarlo portfolio(num_samples, mu, sigma, alpha, alpha1, xmin, nu, dist_type);
    portfolio.run();
    double VaR = portfolio.calculateVaR();
    portfolio.show();

    return 0;
}
