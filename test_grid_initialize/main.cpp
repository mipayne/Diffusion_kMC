//
//  main.cpp
//  test_grid_initialize
//
//  Created by Madelyn Payne on 6/2/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array>
#include <math.h>


void initializeSimpleSystem( int side_length, std::vector<std::array<int,2>> *out)
{
    /*Given: evenly split blocks of A and B atoms on nXn grid
     one vacancy generated at middle     */
    int num_lattice_sites = side_length^2;
    out -> resize(num_lattice_sites);
    //create grid
    for (int num = 0; num < num_lattice_sites;)
    {
        
        for (int j = 0; j < side_length; ++j )
        {
            for (int i = 0; i < side_length; ++i, ++num)
            {
                std::cout << "state position number: " << num << std::endl;
                (*out)[num][0] = i;
                (*out)[num][1] = j;
                std::cout <<"{"<< (*out)[num][0]<< "," << (*out)[num][1] << "}"<< std::endl;

            }
        }
    }
}

int main()
{
    std::vector<std::array<int,2>> grid_array;
    initializeSimpleSystem( 4, &grid_array);
}
