//
//  firstTry.cpp
//  kMC
//
//  Created by Madelyn Payne on 5/2/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <math.h>
//std default random engine

template <typename T>//source:http://www.cplusplus.com/forum/articles/17108/
class Array2D
{
public:
    // constructor
    Array2D(unsigned wd,unsigned ht)
    : nWd(wd), nHt(ht), pAr(0)
    {
        if(wd > 0 && ht > 0)
            pAr = new T[wd * ht];
    }
    
    // destructor
    ~Array2D()
    {
        delete[] pAr;
    }
    
    // indexing (parenthesis operator)
    //  two of them (for const correctness)
    
    const T& operator () (unsigned x,unsigned y) const
    {  return pAr[ y*nWd + x ];   }
    
    T& operator () (unsigned x,unsigned y)
    {  return pAr[ y*nWd + x ];   }
    
    // get dims
    unsigned GetWd() const { return nWd; }
    unsigned GetHt() const { return nHt; }
    
    
    // private data members
private:
    unsigned nWd;
    unsigned nHt;
    T*       pAr;
    
    // to prevent unwanted copying:
    Array2D(const Array2D<T>&);
    Array2D& operator = (const Array2D<T>&);
};

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
int nu = 1e13;              //cycles/sec


/*QUESTION: Problem statement says Ea depends on the atom in the swap
 does that mean that an atom needs energy Ea to swap with any other atom?*/

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
    return nu*activation;
}


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

double probDistribution_first_escape(int i, int j, int time)
{
    return k[i][j] * exp(-k[i][j]*time);
}

int t_draw(int k_value)
{
    //draw random int between 0 and 1
    int r = rand() % 1 + 1;
    //get draw time
    double lnr = log(r);
    
    int x = -1/k_value *lnr;
    return x;
}


int main()
{
    // int bad[4][5];
    Array2D<int> good(4,5);
    
    // bad[1][2] = 3;
    good(1,2) = 3;
    std::cout << good.GetWd()<<std::endl;
    std::cout << good(4,5)<<std::endl;
    //check if array created correctly:
    //create_k_array(5,E);
    
    
    
    //double x = getk(E);
    return 0;
}
