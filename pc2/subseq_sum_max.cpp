#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <tuple>
#include <chrono>
#include <random>
#include <string>
#include <sstream>
#include <fstream>

/*std::pair<int, int> maxSumSubsequence_DC(std::vector<int> items)
{
    int m = 0;
    int p = 0;
    //TODO: impl start condition

    maxSumSubsequenceCore_DC(items, 0, items.size()-1);

    return {m, p};
}

std::pair<int, int> maxSumSubsequenceCore_DC(std::vector<int> items, int i, int j)
{
    int m = 0;
    int p = 0;
    //TODO : impl recursion, start condition

    maxSumSubsequenceCore_DC(items, i, j-2);
    maxSumSubsequenceCore_DC(items, i+1, j-1);


    return {m, p};
}*/

// Kadane’s Algorithm
int maxSumSubsequence_FB(std::vector<int> items)
{
    int res = items[0];

    // Outer loop for starting point of subarray
    for (int i = 0; i < items.size(); i++)
    {
        int currSum = 0;

        // Inner loop for ending point of subarray
        for (int j = i; j < items.size(); j++)
        {
            currSum = currSum + items[j];

            // Update res if currSum is greater than res
            res = std::max(res, currSum);
        }
    }
    return res;
}

// std::tuple<int, int, int> maxSumSubsequence_DV(std::vector<int> items, int m, int p)
//  Find the maximum possible sum in arr[] such that arr[m]
//  is part of it
int maxCrossingSum(std::vector<int> &items, int l, int m, int h)
{

    // Include elements on left of mid.
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        sum = sum + items[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    // Include elements on right of mid
    sum = 0;
    int rightSum = INT_MIN;
    for (int i = m + 1; i <= h; i++)
    {
        sum = sum + items[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    // Return the sum of maximum left, right, and
    // cross subarray
    return (leftSum + rightSum);
}

// Returns sum of maximum sum subarray in arr[l..h]
int MaxSum(std::vector<int> &items, int l, int h)
{

    // Invalid Range: low is greater than high
    if (l > h)
        return INT_MIN;

    // Base Case: Only one element
    if (l == h)
        return items[l];

    // Find middle point
    int m = l + (h - l) / 2;

    // Compute the maximum of the three cases:
    int leftSum = MaxSum(items, l, m);
    int rightSum = MaxSum(items, m + 1, h);
    int crossSum = maxCrossingSum(items, l, m, h);

    // Return the maximum of the three
    if (leftSum >= rightSum && leftSum >= crossSum)
        return leftSum;
    else if (rightSum >= leftSum && rightSum >= crossSum)
        return rightSum;
    else
        return crossSum;
}

int maxSumSubsequence_DV(std::vector<int> &arr)
{
    return MaxSum(arr, 0, arr.size() - 1);
}

void benchmark(int maxSize, std::stringstream &text)
{
    std::random_device rd;                          // Generador aleatorio basado en hardware
    std::mt19937 gen(rd());                         // Motor Mersenne Twister
    std::uniform_int_distribution<> dis(-100, 100); // Números entre 0 y 100

    for (int size = 1; size <= maxSize; size++)
    {
        // create random vector
        std::vector<int> vec;
        vec.reserve(size);
        for (int i = 0; i < vec.capacity(); i++)
        {
            vec.push_back(dis(gen));
        }

        // execute and measure time for maxSumSubsequence_FB
        auto startTime = std::chrono::high_resolution_clock::now();
        maxSumSubsequence_FB(vec);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto ellapsedFB = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

        // execute and measure time for maxSumSubsequence_DV
        auto startTime2 = std::chrono::high_resolution_clock::now();
        maxSumSubsequence_DV(vec);
        auto endTime2 = std::chrono::high_resolution_clock::now();
        auto ellapsedDV = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2);

        text << "(" << size << ellapsedFB.count() << "," << ellapsedDV.count() << ")";
    }
}

int main(int argc, char *argv[])
{
    int size;
    if (argc == 0)
        size = 10;
    else
        size = std::atoi(argv[1]);

    std::vector<int> items = {1, 3, -5, 4, 0, -1, 2, 4};
    std::cout << maxSumSubsequence_FB(items) << std::endl;
    std::cout << maxSumSubsequence_DV(items) << std::endl;

    std::string fileName = "subseq_sum_max_stats.txt";
    std::ofstream file(fileName);

    std::stringstream stream;
    benchmark(size, stream);

    file.clear();
    file << stream.str();

    file.close();

    return 0;
}