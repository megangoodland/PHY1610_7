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
    int Z = walkerpositions.size(); // number of walkers? This is length of the vector.

    std::random_device rd; // use random_device once to seed the random number generator named mt.
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1); //[0,1)
    
    for (int i=0; i<Z; i++){ // looping through walker positions
            
            double random_num = dist(mt); // gets a random number between 0 and 1
 
            if (random_num < prob) { // if [0,p) move left
                walkerpositions[i] = walkerpositions[i]-1; // move left
                // if that move left caused position to be -1, that segment is actually N-1
                if (walkerpositions[i] < 0){ walkerpositions[i] = (N-1);}
            }
                
            else if (random_num < (2*prob)) { // if [p,2p) move right
                walkerpositions[i] = walkerpositions[i]+1; // move right
                // if that move right caused position to be N, that segment is actually 0
                if (walkerpositions[i] > (N-1)){ walkerpositions[i] = 0;}
            }      
    }
        

}


