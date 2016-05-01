#ifndef MG_SOLVER
#define MG_SOLVER
#include "Grid.h"

// The following Stencil stores information about matrix A which is used to multiply A with u
struct Stencil4Point {
        const double c = 4.0;
        const double n =-1.0;
        const double s =-1.0;
        const double w = -1.0;
        const double e = -1.0;
};

// The following stencil is used for full weighting restriction
struct StencilRestrict {
        const double sw=0.0625;   // weightage is 1/16
        const double s=0.125;     // weightage is 1/8
        const double se=0.0625;  
        const double w=0.125;
        const double c=0.250;     // weightage is 1/4
        const double e=0.125;
        const double nw=0.0625;
        const double n=0.125;
        const double ne=0.0625;
};

// The following stencil is used for bilinear interpolation
struct StencilProlong {
        const double center=1.0;
        const double right = 0.5;
        const double up=0.5;
        const double corner = 0.25; 
};                
        
        

class MultiGridSolver {
private: 
        std::vector<Grid*> gridVec_;    // gridVec_ is the imporant data structure of this assignment which stores pointer to various Grid Object formed at each level 
        TwoDimArr u_;                   // This is used to save the u which is set in   
        size_t numLevel_;               // Number of levels 
        size_t cgInd_;                  // cgInd_ means coarse grid index
        const size_t numVcycle_;
        const size_t neu1_;
        const size_t neu2_;
        
        StencilRestrict r_;                     // r stands for restriction
        Stencil4Point s_;                       // s_ stands for stencil update
        StencilProlong p_;                     // p stands for prolongation
        
        void applyRBGS_Iter();
        void applyRestriction();
        void applyInterpolation();
        void applyPreSmoothing();
        void applyPostSmoothing();
        void mgmSolve();
        void computeResidual();
        void displayGrid();
        void displayGridf();
       
        
public:
        MultiGridSolver(const size_t &, const size_t &, const TwoDimArr &);
        ~MultiGridSolver();
        
         void computeSolution();
        TwoDimArr& getSolVec();
        
};

#endif
