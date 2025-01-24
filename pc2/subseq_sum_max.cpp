#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

std::pair<int,int> maxSumSubsequence_FB(std::vector<int> items)
{
    int m = 0;
    int p = 0;

    for(int i = 0; i < items.size();i++)
    {
        for(int j = i; j <= items.size(); j++)
        {
            int newSum = 0;
            int oldSum = 0;
            //TODO
        }
    }
}