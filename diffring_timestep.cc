// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <iostream>
#include <cblas.h>
#include <cmath>

// perform a single time step for the random walkers
void diffring_timestep(const rarray<double,2>& F, rarray<double,1>& P)
{
    ////////////////////////////////////////////////
    //                                            //
    // IMPLEMENT THIS AS PART OF YOUR ASSIGNMENT! //
    //                                            //
    ////////////////////////////////////////////////
}

// fill the matrix needed in perform_time_step
void diffring_fill_timestep_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
    int n = F.extent(0); // F will be a square matrix
    double a = (D*dt)/(pow(dx,2.0)); // This is our 'alpha'
    // Matrix will have (1-2a) on the diagonal, a in the spots beside the diagonal
    // This is for the whole matrix other than F[0][N-1] and F[N-1][0], which are also a
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==j) F[i][j] = 1-(2*a); // on the diagonal put 1-2a
            else if (i==j+1) F[i][j] = a; // on the right side of diagonal put a
            else if (i==j-1) F[i][j] = a; // on the left side of diagonal put a
            else F[i][j] = 0; // otherwise, 0
        }
    }
    // Adding ring boundary conditions:
    F[0][n-1]=a;
    F[n-1][0]=a;
    std::cout << F << std::endl; // want to make sure it worked
}
