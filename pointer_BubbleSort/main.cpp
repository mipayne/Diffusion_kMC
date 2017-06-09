//
//  main.cpp
//  pointer_BubbleSort
//
//  Created by Madelyn Payne on 6/5/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <vector>

void BubbleSort(std::vector<int> *num_vector)
{
    num_vector -> resize(num_vector -> size());
    for (int i = 0; i < num_vector -> size(); ++i)
    {
        for (int j = i + 1; j< num_vector -> size(); ++j)
        {
            if((*num_vector)[j] < (*num_vector)[i])
            {
                int temp;
                temp = (*num_vector)[i];
                (*num_vector)[i] = (*num_vector)[j];
                (*num_vector)[j] = temp;
            }
        }
    }
    
}
int main()
{
    std::vector<int> random_vector = {5,2,4,1};
    BubbleSort(&random_vector);
    for(int k = 0; k < random_vector.size(); ++k)
    {
        std::cout<< random_vector[k] <<std::endl;
    }
    return 0;
}
