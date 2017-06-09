//
//  main.cpp
//  stringstream_play
//
//  Created by Madelyn Payne on 6/6/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <vector>
#include <array>
#include <map>

int main ()
{
    std::map<int,int> stateV_num_coord_map;
    
    std::vector<std::array<int,2>> grid_array = { {{1,2}}, {{3,4}} };
    for(int i = 0; i < grid_array.size();++i)
    {

        //std::cout <<grid_array[i][0]<<grid_array[i][1] << std::endl;
        
        std::stringstream ss;
        
        ss << grid_array[i][0]<< grid_array[i][1] ;
        
        int coordString;
        ss >> coordString;
        std::cout << "stuff: " << coordString << '\n';
        stateV_num_coord_map[coordString] = i;
    }

    std::cout <<stateV_num_coord_map[12];
    std::cout << '\n'<<stateV_num_coord_map[34]<<std::endl;
    return 0;
}
