#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <tuple>
#include <chrono>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>

std::string largeCommonSubseqFBH(std::string &s1, std::string &s2, int m, int n)
{
    if (m == 0 || n == 0)
    {
        return "";
    }
    if (s1[m - 1] == s2[n - 1])
    {
        std::string result = largeCommonSubseqFBH(s1, s2, m - 1, n - 1);
        result.push_back(s1[m - 1]);
        return result;
    }
    else
    {
        std::string result1 = largeCommonSubseqFBH(s1, s2, m - 1, n);
        std::string result2 = largeCommonSubseqFBH(s1, s2, m, n - 1);
        if (result1.size() < result2.size())
        {
            return result2;
        }
        else
        {
            return result1;
        }
    }
}

void largeCommonSubseqFB(std::string s1, std::string s2)
{
    std::string result = largeCommonSubseqFBH(s1, s2, s1.size(), s2.size());
    std::cout << "Largest common subsequence (FB): " << result << std::endl
              << "Length: " << result.size() << std::endl;
}

std::string largeCommonSubseqPDH(std::string &s1, std::string &s2)
{
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<std::string>> table(m + 1, std::vector<std::string>(n + 1, ""));

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                table[i][j] = table[i - 1][j - 1] + s1[i - 1];
            }
            else
            {
                if (table[i - 1][j].size() < table[i][j - 1].size())
                {
                    table[i][j] = table[i][j - 1];
                }
                else
                {
                    table[i][j] = table[i - 1][j];
                }
            }
        }
    }
    return table[m][n];
}

void largeCommonSubseqPD(std::string &s1, std::string &s2)
{

    std::string result = largeCommonSubseqPDH(s1, s2);
    std::cout << "Largest common subsequence (PD): " << result << std::endl
              << "Length: " << result.size() << std::endl;
}

std::string generateRandomString(size_t length, std::string characters,std::uniform_int_distribution<> dist,std::mt19937 gen)
{
    std::string randomString;
    for (size_t i = 0; i < length; ++i)
    {
        randomString += characters[dist(gen)];
    }
    return randomString;
}

void benchmark(int maxSize, std::stringstream &text)
{
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;  // Generador de números aleatorios basado en hardware
    std::mt19937 gen(rd()); // Motor de generación de números aleatorios
    std::uniform_int_distribution<> dist(0, characters.size() - 1);
    for (int size = 1; size <= maxSize; size++)
    {
        std::string str1 = generateRandomString(size, characters, dist, gen);
        std::string str2 = generateRandomString(size, characters, dist, gen);

        // execute and measure time for maxSumSubsequence_FB
        auto startTime = std::chrono::high_resolution_clock::now();
        largeCommonSubseqFB(str1, str2);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto ellapsedFB = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

        // execute and measure time for maxSumSubsequence_DV
        auto startTime2 = std::chrono::high_resolution_clock::now();
        largeCommonSubseqPD(str1, str2);
        auto endTime2 = std::chrono::high_resolution_clock::now();
        auto ellapsedDV = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2);

        text << "(" << size << "," << ellapsedFB.count() << "," << ellapsedDV.count() << "),";
    }
}

int main(int argc, char *argv[])
{
    int size;
    if (argc == 0)
        size = 10;
    else
        size = std::atoi(argv[1]);

    // std::string s1 = "f34rrfgdruu56";
    // std::string s2 = "47etyhgfhd5";

    // largeCommonSubseqFB(s1, s2);
    // largeCommonSubseqPD(s1, s2);

    std::string fileName = "large_common_subseq_stats.txt";
    std::ofstream file(fileName);

    std::stringstream stream;
    benchmark(size, stream);

    file.clear();
    file << stream.str();

    file.close();
}