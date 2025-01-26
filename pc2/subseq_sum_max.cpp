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
std::tuple<int, int, int> maxSumSubsequence_FB(std::vector<int> items)
{
    int res = items[0];
    int maxEnding = items[0];
    int startIndex = 0;
    int endIndex = 0;
    for (int i = 1; i < items.size(); i++)
    {

        // Find the maximum sum ending at index i by either extending
        // the maximum sum subarray ending at index i - 1 or by
        // starting a new subarray from index i
        //maxEnding = std::max(maxEnding + items[i], items[i]);
        if(items[i]<=maxEnding + items[i]){
            maxEnding=maxEnding + items[i];
            endIndex=i;
        } else {
            startIndex=i;
            endIndex=i;
            maxEnding=items[i];
        }
        // Update res if maximum subarray sum ending at index i > res
        res = std::max(res, maxEnding);
    }
    return {res,startIndex,endIndex};
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

// std::tuple<int, int, int>; // start,end, sum

/*std::tuple<int, int, int> subvector_central(std::vector<int> v, int c, int f)
{
    // variables locales
    int m, suma, suma_max;
    int inicio, final;
    std::tuple<int, int, int> optimo;
    m = (c + f) / 2;
    suma_max = INT_MIN;
    suma = 0;
    int lon = v.size() - 1;
    inicio = m - lon + 1;
    final = m + lon - 1;
    if (inicio < 0)
    {
        inicio = 0;
    };
    if (final > n - 1) //TODO: que crjs es n
    {
        for (int i = inicio; i <= n - lon; i++)
        { // se hara n-lon-inicio+1 veces
            suma = 0;
            for (int j = 0; j < lon; j++)
            { // se hara lon veces
                suma = suma + v[j + i];
            };
            if (suma >= suma_max)
            {
                suma_max = suma;
                optimo = {i, i + lon - 1, suma_max};
            };
        };
    }
    else
    {
        for (int i = inicio; i <= m; i++)
        { // se hara m-inicio+1 veces
            suma = 0;
            for (int j = 0; j < lon; j++)
            { // se hara lon veces
                suma = suma + v[j + i];
            };
            if (suma >= suma_max)
            {
                suma_max = suma;
                optimo = {i, i + lon - 1, suma_max};
            };
        };
    };
    return optimo;
}
std::tuple<int, int, int> subvector_optimo(std::vector<int> v, int c, int f)
{
    // Variables locales
    int lon = v.size() - 1;
    std::tuple<int, int, int> izq, der, cent; // Se divide el vector en tres subvectores
    std::tuple<int, int, int> optimo;         // valor devuelto por el metodo
    int m, i;
    int suma = 0;
    int tamanio_izq, tamanio_der;
    if (f - c + 1 <= lon)
    {
        for (i = c; i <= f; i++)
        {
            suma = suma + v[i];
        };
        optimo = {c, f, suma};
    }
    else
    {
        m = (c + f) / 2;
        izq = subvector_optimo(v, c, m);
        tamanio_izq = std::get<1>(izq) - std::get<0>(izq) + 1;
        if (tamanio_izq < lon)
        {
            while (tamanio_izq < lon)
            {
                std::get<1>(izq)++;
                std::get<2>(izq) += v[std::get<1>(izq)];
                tamanio_izq++;
            }
        }
        der = subvector_optimo(v, m + 1, f);
        tamanio_der = std::get<1>(der) - std::get<0>(der) + 1;
        if (tamanio_der < lon)
        {
            while (tamanio_der < lon)
            {
                std::get<0>(der)--;
                std::get<2>(der) += v[std::get<0>(der)];
                tamanio_der++;
            }
        }
        cent = subvector_central(v, c, f);
        if (std::get<2>(izq) >= std::get<2>(der))
        {
            if (std::get<2>(izq) >= std::get<2>(cent))
                optimo = izq;
            else
                optimo = cent;
        }
        else if (std::get<2>(der) >= std::get<2>(cent))
            optimo = der;
        else
            optimo = cent;
    };
    return optimo;
}; // fin subvector_optimo*/
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

    // std::vector<int> items = {1, 3, -5, 4, 0, -1, 2, 4};
    // std::cout << maxSumSubsequence_FB(items) << std::endl;
    // std::cout << maxSumSubsequence_DV(items) << std::endl;

    std::string fileName = "subseq_sum_max_stats.txt";
    std::ofstream file(fileName);

    std::stringstream stream;
    benchmark(size, stream);

    file.clear();
    file << stream.str();

    file.close();

    return 0;
}