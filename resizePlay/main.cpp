//
//  main.cpp
//  resizePlay
//
//  Created by Madelyn Payne on 6/2/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <vector>

int main() {
    // insert code here...
    std::vector<int> myvector;
    std::cout<< myvector.size() << std::endl;
    std::cout<< myvector.capacity() << std::endl;
    myvector.reserve(1);
    std::cout<< myvector.size() << std::endl;
    std::cout<< myvector.capacity() << std::endl;
    myvector.push_back(5);
    std::cout<< "first element of my vector " << myvector.at(0)<<std::endl;
    myvector.at(0) = 7;
    std::cout<< "first element of my vector " << myvector.at(0)<<std::endl;
    myvector.push_back(4);
    std::cout<< "2nd element of my vector " << myvector.at(1)<<std::endl;
    std::cout<< myvector.size() << std::endl;
    std::cout<< myvector.capacity() << std::endl;
    return 0;
}
