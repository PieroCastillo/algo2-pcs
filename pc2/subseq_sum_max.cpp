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

    return {m, p-1};
}



std::tuple<int,int,int> maxSumSubsequence_DV(std::vector<int> items,int m, int p){
    if(m==p){
        return {m,p,items.at(m)};
    }

    int sum=0;
    for(int i=m;i<=p;++i){
        sum+=items.at(i);
    }
    std::tuple<int,int,int> tupleLeft = maxSumSubsequence_DV(items,m,p-1);
    std::tuple<int,int,int> tupleRight = maxSumSubsequence_DV(items,m+1,p);

    if(sum>std::get<2>(tupleLeft)){
        if(sum>std::get<2>(tupleRight)){
            return {m,p,sum};
        } else {
            if(std::get<2>(tupleLeft)>std::get<2>(tupleRight)){
                return tupleLeft;
            } else {
                return tupleRight;
            }
        }
    } else {
        if(std::get<2>(tupleLeft)>std::get<2>(tupleRight)){
            return tupleLeft;
        } else {
            return tupleRight;
        }
    }
}

void maxSumSubsequence(std::vector<int> items){
    std::pair<int,int> pairAnswer = maxSumSubsequence_FB(items);

    std::cout << "Maxima subsecuencia (FB): [ ";
    int sumFB=0;
    for(int i=std::get<0>(pairAnswer);i<=std::get<1>(pairAnswer);++i){
        sumFB+=items.at(i);
        std::cout << items.at(i) << " , ";
    }
    std::cout   << "]"                                                                              << std::endl
                << "Suma: "   << sumFB                                                              << std::endl
                << "Indices: "<< std::get<0>(pairAnswer)   <<  " - " << std::get<1>(pairAnswer)     << std::endl 
                << std::endl;
    
    std::tuple<int,int,int> tupleAnswer = maxSumSubsequence_DV(items,0,items.size()-1);
    std::cout << "Maxima subsecuencia (DV): [ ";
    for(int i=std::get<0>(tupleAnswer);i<=std::get<1>(tupleAnswer);++i){
        std::cout << items.at(i) << " , ";
    }
    std::cout   << "]"                                                                              << std::endl
                << "Suma: "   << std::get<2>(tupleAnswer)                                           << std::endl
                << "Indices: "<< std::get<0>(tupleAnswer)   <<  " - " << std::get<1>(tupleAnswer)   << std::endl;
}

int main(){
    std::vector<int> items = {1,3,-5,4,0,-1,2,4};
    maxSumSubsequence(items);
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