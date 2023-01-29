#ifndef DENSITIES_1_H
#define DENSITIES_1_H


class dist
{
public:

    enum DisType {normal, pareto, student};
    dist(double param1_, double param2_, DisType TheDisType_); // Constructor takes two params at least and the type of distribution we want
    double compute();

private:
    double param1;
    double param2;
    DisType TheDisType;

};


#endif
