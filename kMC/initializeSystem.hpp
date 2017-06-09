//
//  initializeSystem.hpp
//  kMC
//
//  Created by Madelyn Payne on 6/6/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#ifndef initializeSystem_h
#define initializeSystem_h
#include <map>
#include <array>
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


#endif /* initializeSystem_h */
