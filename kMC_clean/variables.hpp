//
//  variables.hpp
//  kMC
//
//  Created by Madelyn Payne on 6/7/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#ifndef variables_hpp
#define variables_hpp

#include <stdio.h>
#include <iostream>

//establish variables
const int g_side_length(9);         //grid side length
const double k_beV = 8.617e-5;    // eV/K
const double Ea = 0.75;              //eV
const double Eb = 0.35;              //eV
const double T = 298;                // K; 25 deg C
const double vib_freq = 1e13;        //cycles/sec
const int g_out_of_range = 82;       //out of range int for grid coordinates

#endif /* variables_hpp */
