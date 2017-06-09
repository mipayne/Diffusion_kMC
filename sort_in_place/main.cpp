//
//  main.cpp
//  sort_in_place
//
//  Created by Madelyn Payne on 6/5/17.
//  Copyright © 2017 Madelyn Payne. All rights reserved.
//

#include <iostream>
#include <vector>

void BubbleSort(std::vector<int> num_vector)
{
    num_vector.resize(num_vector.size());
    for (int i = 0; i < num_vector.size(); ++i)
    {
        for (int j = i + 1; j< num_vector.size(); ++j)
        {
            if(num_vector[j] < num_vector[i])
            {
                int temp;
                temp = num_vector[i];
                num_vector[i] = num_vector[j];
                num_vector[j] = temp;
            }
        }
    }
    for(int k = 0; k < num_vector.size(); ++k)
    {
        std::cout<< num_vector[k] <<std::endl;
    }

}
int main()
{
    std::vector<int> random_vector = {5,2,4,1};
    BubbleSort(random_vector);
    return 0;
}
