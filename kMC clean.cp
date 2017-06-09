//
//  main.cpp
//  kMC
//
//  Created by Madelyn Payne on 4/19/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <random>
#include <array>
#include <map>
#include <sstream>
#include <string>
#include <list>
#include "initializeSystem.hpp"

//Create Random Engine Generator
std::default_random_engine randomEngine1;
//draw random int between 0 and 1
std::uniform_real_distribution<double> distribution(0.0, 1);

//establish variables
//const double k_bJ = 1.38e-23;     // J/K
const double k_beV = 8.617e-5;    // eV/K
//const int E = 1;                  //eV
const double Ea = 0.75;              //eV
const double Eb = 0.35;              //eV
const double T = 298;                // K; 25 deg C
const double vib_freq = 1e13;        //cycles/sec
const int g_out_of_range = 82;       //out of range int for grid coordinates

//initialize system
void initializeSimpleSystem( int side_length, std::vector<std::array<int,2>> *out);//defined in initializeSystem.cpp
void BubbleSort_xCoord(std::vector<State> *num_vector);//defined in initializeSystem.cpp
void initialGrid(std::vector<State> *stateVector,std::map<int,int> *outCoordmap,std::array<int,2> *outVcoord );
void visualize_row(std::vector<State> row);//defined in initializeSystem.cpp
void visualizeGrid (std::vector<State> *stateVector);

//getPossible Vacancy Transitions found in file test_state_pointer
void getPossibleTransitions(std::array<int,2> state,std::vector<std::array<int,2>> *out);

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
    std::cout<< "Has an activation Energy: " << energy<<std::endl;
    double x = -energy/(k_beV*T);
    double activation = exp(x);
    std::cout << "K value in 1/s: " << vib_freq*activation << std::endl;
    return vib_freq*activation;
}


double t_draw(double k_tot)
{
    //get draw time
    double r = distribution(randomEngine1);
    double lnr = std::log(r);
    double x = -1/k_tot *lnr;
    return x;
}

int getJump(std::vector<std::array<int,2>> transitions, std::vector<State> stateVector, double *outKtot, std::map<int,int> *outVCoordMap,  std::array<int,2> *outVbuff)
{
    //search the state of the system for x and y coordinates that match the x and ycoords of the transitions
    // from there get the state_type associated with those coordinates
    
    //using sstream make transition coords into int
    std::vector<std::array<int,2>> transCoordsVector;
    transCoordsVector.resize(4);
    for (int trans = 0; trans < transitions.size();++trans)
    {
        if (transitions[trans][0] > 0 && transitions[trans][1] > 0)
        {
            std::stringstream coord_ss;
            coord_ss << transitions[trans][0]<< transitions[trans][1];
            int coords;
            coord_ss >> coords;
            std::cout<< "Coords: " << coords << '\n';
            //now that we have the coords as an int -> get the entry number in stateVector
            char type = stateVector[(*outVCoordMap)[coords]].state_type;
            transCoordsVector[trans][0] = type;
            transCoordsVector[trans][1] = coords;
        }
        else
        {
            transCoordsVector[trans][0] = 'N';
            transCoordsVector[trans][1] = g_out_of_range;
        }
        
    }
    //plug state_type into
    int num_transitions = 4;
    double k_list[4] = {};
    double k = 0;
    for ( int i = 0; i < num_transitions;++i)
    {
        if (transCoordsVector[i][0] == 'N')
        {
            k = 0;//chosen transition can never go out of range
        }
        else
        {
            k = calc_k(transCoordsVector[i][0]);
        }
        k_list[i] = k;
    }
    //double k_left = calc_k(transCoordsVector[0][0]);
    //double k_right = calc_k(transCoordsVector[1][0]);
    //double k_up = calc_k(transCoordsVector[2][0]);
    //double k_down = calc_k(transCoordsVector[3][0]);
    //double k_list[] = {k_left,k_right,k_up, k_down};
    double result[4];
    std::partial_sum(k_list,k_list+4,result);
    *outKtot = result[3]; //final sum of k's
    //create mapping to know what way the vacancy moved
    std::map<int, std::string> TransMap;
    TransMap[0] = "left";
    TransMap[1] = "right";
    TransMap[2] = "up";
    TransMap[3] = "down";
    
    double random_num = distribution(randomEngine1);
    int multiplier = random_num*(*outKtot);
    int TheTransition;
    std::cout << "using default partial_sum: ";
    for (int i=0; i<num_transitions; i++)
    {
        std::cout << result[i] << ' ';
        std::cout << '\n';
        if (result[i] > multiplier)
        {
            std::string transMade = TransMap[i];
            std::cout<<"Transition to the " << TransMap[i] << std::endl;
            std::cout<< "Transition Coords: {"<< transitions[i][0]<< "," << transitions[i][1]<< "}"<<std::endl;
            (*outVbuff)[0] = transitions[i][0];
            (*outVbuff)[1] = transitions[i][1];
            std::cout<< "vacancy buffer updated"<<std::endl;
            std::cout<< "Trans Coords: " << transCoordsVector[i][1] << std::endl;
            TheTransition = transCoordsVector[i][1];
            break;
        }

    }
    return TheTransition;
}

void updateSystem(std::vector<State> *stateVector, int transCoord, int VCoord,std::map<int,int> *outCoordmap );

int getVCoordsF(std::array<int,2> *inVCoord)
{
    std::stringstream VCoords_ss;
    VCoords_ss << (*inVCoord)[0]<< (*inVCoord)[1];
    int VCoords;
    VCoords_ss >> VCoords;
    std::cout<< "Vacancy Coords: " << VCoords << '\n';
    return VCoords;
}

int main()
{
    //sum of possible transition rate
    double ktot;
    //system time
    double totaltime = 0;
    std::cout<<"Total time: " <<totaltime<<std::endl;
    //maps coordinates to index in statevector
    std::map<int,int> stateV_num_coord_map;
    //holds coordinates of vacancy
    std::array<int,2> vacancy_coord;
    //holds coordinates of next vacancy transition
    std::array<int,2> vacancy_coord_buff;
    
    
    //Intialize Grid
    std::vector<State> stateVector;
    initialGrid(&stateVector,&stateV_num_coord_map,&vacancy_coord);
    visualizeGrid(&stateVector);
    
    //Possible Transitions
    std::vector<std::array<int,2>> transitions;
    getPossibleTransitions(vacancy_coord, &transitions);
    //print coordinates of possible transitions
    std::cout<< "left: {"<< transitions[0][0]<< "," << transitions[0][1] << "}" <<std::endl;
    std::cout<< "right: {"<< transitions[1][0]<< "," << transitions[1][1] << "}" <<std::endl;
    std::cout<< "up: {"<< transitions[2][0]<< "," << transitions[2][1] << "}" <<std::endl;
    std::cout<< "down: {"<< transitions[3][0]<< "," << transitions[3][1] << "}" << std::endl;
    
    //Take Transition
    int TheTransition = getJump(transitions, stateVector, &ktot, &stateV_num_coord_map, &vacancy_coord_buff);
    
    //Update System
    int getVCoords = getVCoordsF(&vacancy_coord);
    updateSystem(&stateVector, TheTransition , getVCoords,&stateV_num_coord_map);
    //update vacancy coord
    vacancy_coord[0] = vacancy_coord_buff[0];
    vacancy_coord[1] = vacancy_coord_buff[1];
    std::cout<< "Vacancy Coord Updated: {"<<vacancy_coord[0]<<","<< vacancy_coord[1]<< "}"<<std::endl;
    visualizeGrid(&stateVector);
    
    
    //add tdraw to totaltime
    double time = t_draw(ktot);
    totaltime += time;
    std::cout<< "t_draw: " << time << " seconds total_time: " << totaltime<< " seconds\n";
    //repeat
    std::cout<< "FINISHED FIRST TRANSITION!" << std::endl;
    
    return 0;
}
