#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

std::pair<int, int> maxSumSubsequence_FB(std::vector<int> items)
{
    int m = 0;
    int p = 0;

    for (int i = 0; i < items.size(); i++)
    {
        for (int j = i; j <= items.size(); j++)
        {
            int newSum = 0;
            int oldSum = 0;
            for (int k = i; k <= j; k++)
            {
                newSum += items[k];
            }
            for (int k = m; k <= p; k++)
            {
                oldSum += items[k];
            }
            if (newSum > oldSum)
            {
                m = i;
                p = j;
            }
        }
    }

    return {m, p};
}

