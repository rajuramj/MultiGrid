#ifndef GRID_H
#define GRID_H

#include "TwoDimArr.h"

//#define _USE_MATH_DEFINES
#define M_PI  3.141592653589793
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
//#include <exception>
#include <cstring>
#include <cassert>

class Grid {
public:       
        Grid(const size_t&);
        ~Grid(){};
        //static Grid createInstance(const size_t &n);
        double h_;
        size_t numGrid_;
        TwoDimArr f_;
        TwoDimArr res_;
        TwoDimArr u_;
};

#endif
