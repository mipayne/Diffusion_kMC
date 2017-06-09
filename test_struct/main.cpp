//
//  main.cpp
//  test_struct
//
//  Created by Madelyn Payne on 6/2/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <string>

const int g_side_length(4);
std::map<int,int> stateV_num_coord_map;

struct State
{/*characterizes a coordinate with state:
  states: A --> A atom
          B --> B atom
          V --> Vacancy */
public:
    int xcoordinate;
    
    int ycoordinate;
    
    char state_type;
};


void initializeSimpleSystem( int side_length, std::vector<std::array<int,2>> *out)
{
    /*Given: evenly split blocks of A and B atoms on nXn grid
     one vacancy generated at middle     */
    int num_lattice_sites = side_length*side_length;
    out -> resize(num_lattice_sites);
    //create grid
    for (int num = 0; num < num_lattice_sites;)
    {
        for (int j = 0; j < side_length; ++j )
        {
            for (int i = 0; i < side_length; ++i, ++num)
            {
                (*out)[num][0] = i;
                (*out)[num][1] = j;
                std::cout <<"{"<< (*out)[num][0]<< "," << (*out)[num][1] << "}"<< std::endl;
                std::cout << "number: " << num << std::endl;
            }
        }
    }
}

void BubbleSort_xCoord(std::vector<State> *num_vector)
{
    num_vector -> resize(num_vector -> size());
    for (int i = 0; i < num_vector -> size(); ++i)
    {
        for (int j = i + 1; j< num_vector -> size(); ++j)
        {
            if((*num_vector)[j].xcoordinate < (*num_vector)[i].xcoordinate)
            {
                State temp;
                temp = (*num_vector)[i];
                (*num_vector)[i] = (*num_vector)[j];
                (*num_vector)[j] = temp;
                
            }
        }
    }
}

void visualize_row(std::vector<State> row)
{
    BubbleSort_xCoord(&row);
    for(int k= 0; k< row.size(); ++k)
    {
        std::cout<< row[k].state_type << " ";
        
        //std::cout<< "{"<<row[k].xcoordinate <<","<<row[k].ycoordinate << "}"<<std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    // create empty vector for grid
    std::vector<std::array<int,2>> grid_array;
    // initialize simple grid
    initializeSimpleSystem( g_side_length, &grid_array);
    // prepare variables
    int side_length = sqrt(grid_array.size());
    std::vector<State> stateVector;
    stateVector.reserve(grid_array.size());
    
    for (int pos = 0; pos < grid_array.size(); ++pos)
    {
        //fill Coordinates -> stateVector number map
        std::stringstream ss;
        ss << grid_array[pos][0] << grid_array[pos][1];
        int coordString;
        ss >> coordString;
        std::cout<< "CoordString: " << coordString << '\n';
        stateV_num_coord_map[coordString] = pos;
        
        //fill State vector
        State position;
        position.xcoordinate = grid_array[pos][0];
        position.ycoordinate = grid_array[pos][1];
        //assign state
        if (position.xcoordinate == side_length/2 && position.ycoordinate == side_length/2)
        {
            //place vacancy in middle
            //std::cout<< "VACANCY\n";
            position.state_type = 'V';
        }
        else if(position.xcoordinate < side_length/2)
        {
            //std::cout<< "A atom\n";
            position.state_type = 'A';
        }
        else
        {
            //std::cout<< "B atom"<< std::endl;
            position.state_type = 'B';
        }
        stateVector.push_back(position);
    }
    
    //Organize states to resemble physical position
    //this part is hard coded; fix later
    std::vector<State> row0;
    row0.reserve(side_length);
    std::vector<State> row1;
    row1.reserve(side_length);
    std::vector<State> row2;
    row2.reserve(side_length);
    std::vector<State> row3;
    row3.reserve(side_length);
    for (int i = 0; i < stateVector.size(); ++i)
    {
        switch (stateVector[i].ycoordinate)
        {
            case 0:
                row0.push_back(stateVector[i]);
                break;
            case 1:
                row1.push_back(stateVector[i]);
                break;
            case 2:
                row2.push_back(stateVector[i]);
                break;
            case 3:
                row3.push_back(stateVector[i]);
                break;
            default:
                std::cout << "I didn't put enough cases!" <<std::endl;
        }
    }
    //Graphic Visual of grid
    visualize_row(row3);
    visualize_row(row2);
    visualize_row(row1);
    visualize_row(row0);
    //Check coordinate stateVector map
    std::cout << stateV_num_coord_map[00]<< '\n';
    std::cout << stateVector[stateV_num_coord_map[00]].state_type<< std::endl;
    std::cout << stateVector[stateV_num_coord_map[22]].state_type<< std::endl;
    return 0;
}

