#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <tuple>
#include <random>

std::pair<int, int> maxSumSubsequence_DC(std::vector<int> items)
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
}

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

int main()
{
    std::random_device rd;                       // Generador aleatorio basado en hardware
    std::mt19937 gen(rd());                      // Motor Mersenne Twister
    std::uniform_int_distribution<> dis(-100, 100); // Números entre 0 y 100

    std::vector<int> vec(10);
    for (auto &num : vec)
    {
        num = dis(gen); // Generar números aleatorios
    }

    // Imprimir el vector
    for (const auto &num : vec)
    {
        std::cout << num << " ";
    }

    return 0;
}