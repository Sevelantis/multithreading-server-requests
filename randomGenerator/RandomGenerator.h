#ifndef P2_RANDOMGENERATOR_H
#define P2_RANDOMGENERATOR_H

#include "../resource/Resource.h"
#include "../constants/Constants.h"
#include <random>

struct RandomGenerator
{
    static const int max = 100000;

    double randDouble(int fmin, int fmax)
    {
        double f = (double)rand() / RAND_MAX;
        return fmin + f * (fmax - fmin);
    }

    static int randInt(int min, int max)
    {
        return rand() % (max - min) + min;
    }

    bool isProbability(double prob)
    {
        int middle = max * prob;
        int rnd = rand() % max;
        
        return (rnd < middle) ? true : false;
    }

    static int randNumOfResources(double probOne, double probTwo, double probThree)
    {
        int one = max * probOne;
        int two = one + max * probTwo;
        int three = two + max * probThree;
        
        int resNum = -1;
        int rnd = rand() % max;

        if(rnd <= one)
            resNum = 1;
        else if(rnd <= two && rnd > one)
            resNum = 2;
        else if(rnd <= three && rnd > two)
            resNum = 3;
        return resNum;
    }

    static int randHalfOrFull(double probOne, double probTwo)
    {
        int one = max * probOne;
        int two = one + max * probTwo;

        int x = -1;
        int rnd = rand() % max;
        if(rnd <= one)
            x = HALF;
        else if(rnd <= two && rnd > one)
            x = FULL;
        return x;
    }
};

#endif // P2_RANDOMGENERATOR_H