#ifndef READ_H
#define READ_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

class Stock
{
public:

    Stock(std::string file_path); // Constructor takes the filepath
    std::vector<double> computeReturns();
    double computeMean(std::vector<double> returns);
    double computeVariance(std::vector<double> returns, double mean);

private:
    std::string file_path;
};


#endif
