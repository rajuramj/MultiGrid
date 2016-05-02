#include "Grid.h"


Grid::Grid(const size_t &level) 
{
        const size_t temp = pow(2,level);
        h_ = 1.0/temp;
        numGrid_ = temp+1;
        const size_t numTotPoints=numGrid_*numGrid_;
        this->f_.data_.resize(numTotPoints,0.0);
        this->res_.data_.resize(numTotPoints,0.0);
        this->u_.data_.resize(numTotPoints,0.0);
        
        std::cout << "Level " << level << " grid constructed with total grid points " << numTotPoints << std::endl;
        
}



/*
This function restricts the GridUtill class to create one object Please do not uncomment this code

Grid Grid::createInstance(const size_t &numLevel)
{
        if(numObjects ==0)
        {
                Grid grid(numLevel);
                numObjects++;
                return grid;
                 
        }
        else
        {
                throw std::string("More than one object creation NOT allowed in the Singelton class\n");
                //return nullptr;
                
        }
        
}
        
*/

        
