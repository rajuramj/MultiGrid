#include "GridUtil.h"
#include "Precision.h"

TwoDimArr& GridUtil::getVec()
{
        return u_;
}

GridUtil::GridUtil(const size_t &level)
{
        size_t temp = pow(2,level);
        numGrid_ = temp+1;
        h_ = 1.0/temp;
        
        u_.data_.resize(numGrid_*numGrid_,0.0);
        f_.data_.resize(numGrid_*numGrid_,0.0);
         
}

GridUtil::~GridUtil()
{
        //Empty Destructor      
}

/*
This function sets the initial boundary conditions defined by function g in the exercise sheet 
*/

void GridUtil::setBCs(bool isNeumannBC)
{
      //real x1,y1,x2,y2;
      real x, y = h_*(numGrid_-1);              // Outer boundary
      size_t size = numGrid_*numGrid_;

      if(!isNeumannBC) // If Boundary condition is only Dirichlet
      {
          //for(size_t i=0, j=(numGrid_-1)*numGrid_; (i<numGrid_) && (j<size); ++i,++j)
          for(size_t j=(numGrid_-1)*numGrid_; j<size; ++j)
              {
                   // x1 = h_*(i%numGrid_);
                    x = h_*(j%numGrid_);
                    //y1 = 0.0;
                   // u_.data_[i] = sin(M_PI*x1)*sinh(M_PI*y1);
                    u_.data_[j] = sin(M_PI*x)*sinh(M_PI*y);
              }
      }

      else
      {

          std::fill(f_.data_.begin(), f_.data_.end(), 2.0 );
          
          // Dirichlet BC on Horizontal walls for Mixed BCs
          for(size_t j=0; j<numGrid_-1; ++j) // Bottom wall
          {
                x = h_*j;
                u_.data_[j] = x*(1-x);
          }

          for(size_t j=size-numGrid_; j<size ; ++j) // Top wall
          {   
                x = h_*(j%numGrid_);
                u_.data_[j] = x*(1-x);
          }

          // Neumann BC on Vertical walls for Mixed BCs
          for(size_t i=numGrid_; i<size-numGrid_; i+=numGrid_)
          {
                u_.data_[i] = u_.data_[i+1] - h_;
          }

          for(size_t i=numGrid_ + (numGrid_-1); i<size-1; i+=numGrid_)
          {
                u_.data_[i] = u_.data_[i-1] - h_;
          }
          
      }
}


/*
This function displays the grid entries u
*/
void GridUtil::displayGrid(const TwoDimArr& arr) const
{
        std::cout << "Grid Entries:\n ";
        
        for(int row=(numGrid_ - 1) ; row>= 0; --row)
        {
                size_t index;
                for(size_t col=0; col<numGrid_; ++col)
                {
                        index = row*numGrid_ + col;
                        //cout << index << "\t"; 
                        std::cout << arr.data_[index] << "\t";
                }        
                
                std::cout << "\n";
        }
}

//This is a overloaded function of displayGrid which prints u_ entries 
void GridUtil::displayGrid() const
{
        std::cout << "Grid Entries:\n ";
        
        for(int row=(numGrid_ - 1) ; row>= 0; --row)
        {
                size_t index;
                for(size_t col=0; col<numGrid_; ++col)
                {
                        index = row*numGrid_ + col;
                        //cout << index << "\t"; 
                        std::cout << this->u_.data_[index] << "\t";

                }        
                
                std::cout << "\n";
        }

   
}

// This function writes the solution to solution.txt that can be visualized by gnuplot
void GridUtil::writeSol(const TwoDimArr& arr) const
{
        std::ofstream f_out("solution.txt");
        //std::ofstream f_act("act.txt");
        //std::ofstream f_err("err.txt");
        real x,y,comp; 
        
        for(size_t i=0; i<numGrid_ ; ++i)
        {
                for(size_t j=0; j<numGrid_ ;++j)
                {
                        x = j*h_ ; 
                        y = i*h_;
                        comp = arr.data_[i*numGrid_+j];
                        /*if(isNeumann)
                                act = x*(1-x);
                        else
                                act = sin(M_PI*x)*sinh(M_PI*y);*/
                        f_out << x << "\t" << y << "\t" << comp << std::endl;
                        //f_act << x << "\t" << y << "\t" << act << std::endl;
                        //f_err << x << "\t" << y << "\t" << fabs(act-comp) << std::endl;
                }        
        }
             
        f_out.close();
        //f_act.close();
        //f_err.close();       

        std::cout << "The solution has been written in solution.txt\n";        
}

// This function writes the error after the Multi Grid solver has been completed
void GridUtil::measureError(const TwoDimArr & a, const bool& isNeumann)
{
	real x,y,act,comp,diff,error = 0.0;
        size_t numInnerPoints = (numGrid_-2)*(numGrid_-2);
	 for(size_t i=0; i<numGrid_ ; ++i)
        {
                for(size_t j=0; j<numGrid_ ;++j)
                {
                        x = j*h_ ; 
                        y = i*h_;
                        comp = a.data_[i*numGrid_+j];
                        if(isNeumann)
                                act = x*(1-x);
                        else
                                act = sin(M_PI*x)*sinh(M_PI*y);
                 	diff = fabs(comp - act);
			error += diff * diff;       
		}        
        }
	
	error = std::sqrt(error/numInnerPoints);
	
	std::ofstream err_out;
	err_out.open("errPlotvsGridSize.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	err_out << h_ << "\t" << error << std::endl;
	err_out.close();
	//std::cout<<"Error between the computed and analytical solution for h = 1/"<<numGrid_-1 <<" is : "<<error<<std::endl;
}
		



	
