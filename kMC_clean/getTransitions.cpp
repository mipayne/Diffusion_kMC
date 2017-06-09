//
//  getTransitions.cpp
//  kMC
//
//  Created by Madelyn Payne on 6/7/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include "variables.hpp"

#include <iostream>
#include <math.h>
#include <vector>
#include <tuple>
#include <random>
#include <array>
#include <map>
#include <sstream>
#include <string>
#include <list>
#include "initializeSystem.hpp"
void getPossibleTransitions(std::array<int,2> state,std::vector<std::array<int,2>> *out)
{
    /*
     INPUTS: state (the current vacancy position)
     std::array<int,2>
     OUTPUTS:
     RETURNS: NONE
     */
    out -> resize(4);
    (*out)[0] = {{state[0] - 1,state[1]}}; /*left*/
    (*out)[1] = {{state[0]+1,state[1]}}; /*right*/
    (*out)[2] = {{state[0],state[1]+1}}; /*up*/
    (*out)[3] = {{state[0],state[1]-1}}; /*down*/
    
}

double calc_k(char state_type)
{
    /*get's k_ij value
     inputs: activation energy required for vacancy to swap with atom a (Ea) or with atom b (Eb)
     outputs: k value for frequency of swaps
     */
    double energy = 0;
    if (state_type == 'A')
    {
        energy = Ea;
    }
    else if (state_type == 'B')
    {
        energy = Eb;
    }
    else
    {
        energy = 0;
        std::cout<<"switching vacancy with vacancy"<< std::endl;
    }
    
    double x = -energy/(k_beV*T);
    double activation = exp(x);
    //rate [1/s]
    return vib_freq*activation;
}

int getVCoordsF(std::array<int,2> *inVCoord)
{
    std::stringstream VCoords_ss;
    VCoords_ss << (*inVCoord)[0]<< (*inVCoord)[1];
    int VCoords;
    VCoords_ss >> VCoords;
    return VCoords;
}

int getTransitions_main()
{
    std::vector<std::array<int,2>> transitions;
    std::array<int,2> vacancy_state = {{0,0}};
    getPossibleTransitions(vacancy_state, &transitions);
    std::cout<< "transitions memory size " << sizeof(transitions) << std::endl;
    std::cout<< "transitions element length " << transitions.size() << std::endl;
    std::cout<< "left: {"<< transitions[0][0]<< "," << transitions[0][1] << "}" <<std::endl;
    std::cout<< "right: {"<< transitions[1][0]<< "," << transitions[1][1] << "}" <<std::endl;
    std::cout<< "up: {"<< transitions[2][0]<< "," << transitions[2][1] << "}" <<std::endl;
    std::cout<< "down: {"<< transitions[3][0]<< "," << transitions[3][1] << "}" << std::endl;
    return 0;
}
