//
//  main.cpp
//  insert_into_vector_play
//
//  Created by Madelyn Payne on 6/2/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//
// inserting into a vector
#include <iostream>
#include <vector>

int main ()
{
    std::vector<int> myvector (3,100);
    std::vector<int>::iterator it;
    
    it = myvector.begin();
    std::cout<< it <<std::endl;//what is it????
    it = myvector.insert ( it , 200 );
    std::cout<< it <<std::endl;///what is it????
    myvector.insert (it,2,300);
    
    // "it" no longer valid, get a new one:
    it = myvector.begin();
    
    std::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());
    
    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);
    
    std::cout << "myvector contains:";
    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
    return 0;
}
