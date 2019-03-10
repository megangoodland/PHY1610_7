// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <iostream>
#include <random>

// Perform a single time step for the random walkers
//
// parameters:
//
//  walkerpositions: the positions of a number of walkers (note that
//                   the number of walker Z can be found from
//                   Z=walkerpositions.size())
//
//  N:               the number of possible positions. All positions
//                   in the walkerpositions array should remain
//                   between 0 and N-1
//
//  prob:            the probability to jump to the left. Also the
//                   probability to just right.  (the probability to
//                   stay on the same spot is thus 1-2p.)
//
// output:
//
//  the content of the walkerpositions arrays should have changed to
//  reflect the random movement of all walker (i.e., they will each
//  have been given a chance to move on position to the left or to
//  the right).
//
void walkring_timestep(rarray<int,1>& walkerpositions, int N, double prob)
{
    //int Z = walkerpositions.size(); // number of walkers
    // want to produce a random number between 0 and 1. 
    rarray<int,1> walkerpositions_new(N); // array to hold new walker positions
    std::random_device rd; // use random_device once to seed the random number generator named mt.
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1); //[0,1)
    
    for (int i=0; i<N; i++){ // looping through walker positions
        int total = walkerpositions[i]; // total is number of walkers in position i
        
        if (total > 0) {
          
            for (int j=0; j<total; j++){ // looping through walkers in position i
                double random_num = dist(mt); // gets a random number between 0 and 1
                
                if (random_num < prob) { // if [0,p) move left
                    if(i=0){walkerpositions_new[N-1]= walkerpositions_new[N-1]+1;} // if we're at 0, it has to go to N-1
                    else {walkerpositions_new[i-1]= walkerpositions_new[i-1]+1;} // otherwise just put it to the left
                }
                
                else if (random_num < (2*prob)) { // if [p,2p) move right
                    if (i=(N-1)){walkerpositions_new[0]= walkerpositions_new[0]+1;} // if we're at the end, it has to go to 0
                    else {walkerpositions_new[i+1]= walkerpositions_new[i+1]+1;} // otherwise just put it to the right
                } 
                
                else { // if [2p, 1) don't move
                    walkerpositions_new[i]= walkerpositions_new[i]+1;} 
            }
        }
    }
    
    for (int k=0; k<N; k++){ // looping through walker positions, copy walkerpositions_new to walker_positions
        walkerpositions_new[k]=walkerpositions[k];
    }
        

}


