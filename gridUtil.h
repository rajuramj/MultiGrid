#ifndef GRIDUTIL_H
#define GRIDUTIL_H

#define _USE_MATH_DEFINES
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <exception>

class GridUtil {
private:
        size_t numGridX_;
        size_t numGridY_;
        double hx_;
        double hy_;
        std::vector<double> u_;
        std::vector<double> f_;
        GridUtil(const size_t&);
        size_t static numObjects;
public:       
        static GridUtil createInstance(const size_t &n);
        void setBCs();
        void displayGrid() const;
        bool isInteriorPoint(const size_t&);
        
};

#endif