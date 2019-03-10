// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <iostream>
#include <rarrayio>
#include <cblas.h>
#include <cmath>
using namespace std;

// perform a single time step for the random walkers
void diffring_timestep(const rarray<double,2>& F, rarray<double,1>& P)
{
    int n = F.extent(0); // F will be a square matrix
    //rarray<double,1> Pi(n); 
    double F2[n][n];
    double P2[n];
    double Pi[n];
    // Have to change array types for cblas_dgemv inputs to work
    for (int i=0; i<n; i++){
        P2[i] = P[i];
        Pi[i] = P[i];  // copying P to Pi, which will hold the previous P vector. P will be P_i+1.
        for (int j=0; j<n; j++){
            F2[i][j] = F[i][j];
        }
    }
    cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1.0, F2[0], n, Pi, 1, 0.0, P2, 1);
    
    // Now copy P2 over to P rarray
    for (int i=0; i<n; i++){ P[i]=P2[i];}
    
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
}
