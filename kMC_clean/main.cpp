//
//  main.cpp
//  kMC_clean
//
//  Created by Madelyn Payne on 6/7/17.
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
#include "variables.hpp"

//Create Random Engine Generator
std::default_random_engine randomEngine1;
//draw random int between 0 and 1
std::uniform_real_distribution<double> distribution(0.0, 1);


//initialize system found in initializeSystem.cpp
void initializeSimpleSystem( int side_length, std::vector<std::array<int,2>> *out);
void BubbleSort_xCoord(std::vector<State> *num_vector);
void initialGrid(std::vector<State> *stateVector,std::map<int,int> *outCoordmap,std::array<int,2> *outVcoord );
void initialGridNew(std::vector<State> *stateVector,std::map<int,int> *outCoordmap,std::array<int,2> *outVcoord,int vacancy_xcoord, int vacancy_ycoord);

void visualize_row(std::vector<State> row);
void visualizeGrid (std::vector<State> *stateVector);

//getPossible Vacancy Transitions found in getTransitions.cpp
void getPossibleTransitions(std::array<int,2> state,std::vector<std::array<int,2>> *out);

double calc_k(char state_type);


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
    /*Inputs: transitions vector
              stateVector
     Outputs: 
              ktot double
              stateV coordinate map
              vacancy coordinate buffer
     Returns:
              the transition coordinates as an int
     */
    //using sstream make transition coords as a single int
    //pass int into map to get the stateVector index of that coordinate
    std::vector<std::array<int,2>> transCoordsVector;
    transCoordsVector.resize(4);
    for (int trans = 0; trans < transitions.size();++trans)
    {
        //fill in transCoordsVector with coords and type
        if (transitions[trans][0] >= 0 && transitions[trans][1] >= 0)
        {
            std::stringstream coord_ss;
            coord_ss << transitions[trans][0]<< transitions[trans][1];
            int coords;
            coord_ss >> coords;
            //use coords as int to access stateVector and get state_type
            char type = stateVector[(*outVCoordMap)[coords]].state_type;
            transCoordsVector[trans][0] = type;
            transCoordsVector[trans][1] = coords;
        }
        // if coordinates are out of grid range, give the state_type 'N' tag
        else
        {
            transCoordsVector[trans][0] = 'N';
            transCoordsVector[trans][1] = g_out_of_range;
        }
        
    }
    //Calculate transition rates for all transitions
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
    double result[4];
    std::partial_sum(k_list,k_list+4,result);
    *outKtot = result[3]; //final sum of k's

    //create mapping to know what way the vacancy moved (for debugging purposes)
    std::map<int, std::string> TransMap;
    TransMap[0] = "left";
    TransMap[1] = "right";
    TransMap[2] = "up";
    TransMap[3] = "down";
    
    //get Transition using random number generated within ktot
    double random_num = distribution(randomEngine1);
    double multiplier = random_num*(*outKtot);
    int TheTransition;
    for (int i=0; i<num_transitions; i++)
    {
        if (result[i] > multiplier)
        {
            std::string transMade = TransMap[i];
            std::cout<<"Transition " << TransMap[i] << std::endl;
            std::cout<< "Transition Coords: {"<< transitions[i][0]<< "," << transitions[i][1]<< "}"<<std::endl;
            (*outVbuff)[0] = transitions[i][0];
            (*outVbuff)[1] = transitions[i][1];
            std::cout<< "vacancy buffer updated"<<std::endl;
            TheTransition = transCoordsVector[i][1];
            break;
        }
        
    }
    return TheTransition;
}

void updateSystem(std::vector<State> *stateVector, int transCoord, int VCoord,std::map<int,int> *outCoordmap );


int getVCoordsF(std::array<int,2> *inVCoord);

void runSimulation(int ivacancy_xcoord, int ivacancy_ycoord, int iterations)
{
    //sum of possible transition rate
    double ktot;
    //system time
    double totaltime = 0;
    //maps coordinates to index in statevector
    std::map<int,int> stateV_num_coord_map;
    //holds coordinates of vacancy
    std::array<int,2> vacancy_coord;
    //holds coordinates of next vacancy transition
    std::array<int,2> vacancy_coord_buff;
    
    //Intialize Grid
    std::vector<State> stateVector;
    initialGridNew(&stateVector,&stateV_num_coord_map,&vacancy_coord,ivacancy_xcoord,ivacancy_ycoord);
    visualizeGrid(&stateVector);
    
    for(int turns =0;turns < iterations;++turns)
    {
        
        //Possible Transitions
        std::vector<std::array<int,2>> transitions;
        getPossibleTransitions(vacancy_coord, &transitions);
        //print coordinates of possible transitions
        std::cout<< ' '<<std::endl;
        std::cout<< "Possible Transitions: "<<std::endl;
        std::cout<< "left: {"<< transitions[0][0]<< "," << transitions[0][1] << "}" <<std::endl;
        std::cout<< "right: {"<< transitions[1][0]<< "," << transitions[1][1] << "}" <<std::endl;
        std::cout<< "up: {"<< transitions[2][0]<< "," << transitions[2][1] << "}" <<std::endl;
        std::cout<< "down: {"<< transitions[3][0]<< "," << transitions[3][1] << "}" << std::endl;
        std::cout<< ' '<<std::endl;
        
        //Take Transition
        int TheTransition = getJump(transitions, stateVector, &ktot, &stateV_num_coord_map, &vacancy_coord_buff);
        
        //Update System
        int getVCoords = getVCoordsF(&vacancy_coord);
        updateSystem(&stateVector, TheTransition , getVCoords,&stateV_num_coord_map);
        //update vacancy coord
        vacancy_coord[0] = vacancy_coord_buff[0];
        vacancy_coord[1] = vacancy_coord_buff[1];
        std::cout<< "Vacancy Coord Updated: {"<<vacancy_coord[0]<<","<< vacancy_coord[1]<< "}"<<std::endl;
        std::cout<< ' '<<std::endl;
        visualizeGrid(&stateVector);
        
        
        //add tdraw to totaltime
        double time = t_draw(ktot);
        totaltime += time;
        //std::cout<< "t_draw: " << time << " seconds"<<std::endl;
        std::cout<<"total_time: " << totaltime<< " seconds\n";
        std::cout<< ' '<<std::endl;
        //repeat
    }

}

int main()
{
    std::cout<<"Vacancy at origin: "<<std::endl;
    runSimulation(0,0,1000);
    std::cout<< "FINISHED SIMULATION!" << std::endl;
    
    std::cout<<"Vacancy in middle: " <<std::endl;
    runSimulation(g_side_length/2,g_side_length/2,1000);
    std::cout<< "FINISHED SIMULATION!" << std::endl;
    return 0;
}

