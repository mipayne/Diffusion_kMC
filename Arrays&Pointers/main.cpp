//
//  main.cpp
//  Arrays&Pointers
//
//  Created by Madelyn Payne on 5/3/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <typeinfo>
#include <math.h>
#include <vector>
#include <tuple>
#include <random>
#include <array>

int notmain()
{
    int array[] = { 9, 7, 5, 3, 1 };
    
    std::cout << "Element 0 is at address: " << &array[0] << '\n';
    std::cout << "Element 1 is at address: " << &array[1] << '\n';
    std::cout << "Element 2 is at address: " << &array[2] << '\n';
    std::cout << "Element 3 is at address: " << &array[3] << '\n';
    
    return 0;
}


bool isDigit(char c)
{
    switch (c)
    {
        case '0': // if c is 0
        case '1': // or if c is 1
        case '2': // or if c is 2
        case '3': // or if c is 3
        case '4': // or if c is 4
        case '5': // or if c is 5
        case '6': // or if c is 6
        case '7': // or if c is 7
        case '8': // or if c is 8
        case '9': // or if c is 9
            return true; // then return true
        default:
            return false;
    }
}
/*Doesn't work because switch requires int
double getTransition(float rand_float, double* transition_energies, double* transitions)
{
    switch(rand_float)//switch may not be the way to go because need int value for argument
    {
        case 0 <= rand_float < transition_energies[0]:
            return_value = transition[0]
        case transtion_energies[0] <= rand_float < transition_energies[1]:
            return_value = transition[1]
        case transtion_energies[1] <= rand_float < transition_energies[2]:
            return_value = transition[2]
        case transtion_energies[2] <= rand_float < transition_energies[3]:
            return_value = transition[3]
        default:
            return_value = Null //How do I branch to an error message?
    }
    return return_value;
}
*/

int notnotmain()
{
    int x(4);
    std::cout << typeid(&x).name()<< std::endl;
    
    return 0;
}

void getPossibleTransitions(std::array<int,2> state,std::vector<std::array<int,2>> *out)
{
    /*
     INPUTS: state (the current vacancy position)
     std::array<int,2>
     OUTPUTS:
     RETURNS: NONE
     */
    out -> resize(4);
    std::cout << state[0] << ',' << state[1] << std::endl;
    (*out)[0] = {{state[0] - 1,state[1]}}; /*left*/
    
    std::cout << "left state is" << (*out)[0][0] << ',' << (*out)[0][1] << std::endl;
    
    (*out)[1] = {{state[0]+1,state[1]}}; /*right*/
    std::cout << "this step happens" << std::endl;
    (*out)[2] = {{state[0],state[1]+1}}; /*up*/
    
    (*out)[3] = {{state[0],state[1]-1}}; /*down*/

}



void printState(int *state)
{
    std::cout << *state << std::endl;
}

int main()
{
    std::vector<std::array<int,2>> transitions;
    std::array<int,2> vacancy_state = {{0,0}};
    getPossibleTransitions(vacancy_state, &transitions);
    std::cout<< "transitions memory size " << sizeof(transitions) << std::endl;
    std::cout<< "transitions element length" << transitions.size() << std::endl;
    std::cout<< "left: {"<< transitions[0][0]<< "," << transitions[0][1] << "}" <<std::endl;
    std::cout<< "right: {"<< transitions[1][0]<< "," << transitions[1][1] << "}" <<std::endl;
    std::cout<< "up: {"<< transitions[2][0]<< "," << transitions[2][1] << "}" <<std::endl;
    std::cout<< "down: {"<< transitions[3][0]<< "," << transitions[3][1] << "}" << std::endl;
    //int array[] = { 9, 7, 5, 3, 1 };
    //int *ptr = &array[0];
    //printState(ptr);
    return 0;
}

