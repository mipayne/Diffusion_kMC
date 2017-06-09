//
//  2ndTry.cpp
//  kMC
//
//  Created by Madelyn Payne on 6/5/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <tuple>
#include <random>
#include <array>

void initializeRandomSystem( int num_lattice_sites, int frac_A, int num_vacancies, std::vector<std::array<int,2>> *out)
{
    //NOT FINISHED
    *out -> resize(num_lattice_sites);
    //randomly distribute A, B, and vacancy atoms
    int num_A = num_lattic_sites*frac_A;
    int num_B = num_lattice_sites - num_A - num_vacancies;
    
}


//std default random engine


int k[5][5];//make for easy reference
int rand (void);

//establish variables
int length_of_side = 5;     //matrix size = 5x5
double k_bJ = 1.38e-23;     // J/K
double k_beV = 8.617e-5;    // eV/K
int E = 1;                  //eV
int Ea = 0.75;              //eV
int Eb = 0.35;              //eV
int T = 298;                // K; 25 deg C
int vib_freq = 1e13;              //cycles/sec

//getPossible Vacancy Transitions found in file test_state_pointer
double calc_k(double energy)
{
    getTransitions(state,std::vector<std::tuple<int,int>>)* out)
}

double calc_k(double energy)
{
    /*get's k_ij value
     inputs: activation energy required for vacancy to swap with atom a (Ea) or with atom b (Eb)
     outputs: k value for frequency of swaps
     */
    double x = -energy/(k_beV*T);
    std::cout << "x:" << x ;
    double activation = exp(x);
    std::cout << nu*activation << std::endl;
    return vib_freq*activation;
}

/*DON'T USE NOT A GOOD WAY TO GET ARRAY
 void create_k_array (int array_side,int energy)
 {
 int k [array_side][array_side];
 for(int i = 0; i < array_side; i++)
 {
 for (int j = 0; j < array_side; j++)
 {
 k[i][j] = calc_k(energy);
 }
 }
 std::cout << k << std::endl;// need to figure out how to use memory location to get array elements
 }
 */

double probDistribution_first_escape(int i, int j, int time)
{
    return k[i][j] * exp(-k[i][j]*time);
}

int t_draw(int k_value)
{
    //draw random int between 0 and 1
    std::uniform_real_distribution<double> distribution(0.0, ktot);
    int r = rand() % 1 + 1;
    //get draw time
    double lnr = log(r);
    
    int x = -1/k_value *lnr;
    return x;
}

float getktot(kenergies)
{
    return std::partial_sum(kenergies.begin(),kenergies.end(),kenergies.begin(), std::plus<>())
}

int* getJump(transitions, transition_energies)
{
    float nrg = getktot(transition_energies)//look at partial sums
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, ktot);
    
    float myrand = distribution(generator);
    
    
}

int main()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1);
    double totaltime;
    
std:vector<std:vector<char>> state;
    
    std::vector<std::tuple<int,int>>transitions;//changed to array
    getTransitions(state,&,transitions)
    //double x = getk(E);
    return 0;
}
