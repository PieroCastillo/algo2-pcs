#include <iostream>
#include <vector>
#include <string>

std::string largeCommonSubseqFBH(std::string &s1,std::string &s2,int m, int n){
    if(m==0||n==0){
        return "";
    }
    if(s1[m-1]==s2[n-1]){
        std::string result=largeCommonSubseqFBH(s1,s2,m-1,n-1);
        result.push_back(s1[m-1]);
        return result;
    } else {
        std::string result1=largeCommonSubseqFBH(s1,s2,m-1,n);
        std::string result2=largeCommonSubseqFBH(s1,s2,m,n-1);
        if(result1.size()<result2.size()){
            return result2;
        } else {
            return result1;
        }
    }
}


void largeCommonSubseqFB(std::string s1,std::string s2){
    std::string result = largeCommonSubseqFBH(s1,s2,s1.size(),s2.size());
    std::cout << "Largest common subsequence (FB): " << result << std::endl
              << "Length: " << result.size()              << std::endl;
}


void largeCommonSubseqPD(std::string &s1,std::string &s2){
    int m=s1.size();
    int n=s2.size();
    std::vector<std::vector<std::string>> table (m+1,std::vector<std::string>(n + 1, ""));

    for(int i=1;i<=m;++i){
        for(int j=1;j<=n;++j){
            if(s1[i-1]==s2[j-1]){
                table[i][j]=table[i-1][j-1] + s1[i-1];
            } else {
                if(table[i-1][j].size()<table[i][j-1].size()){
                    table[i][j]=table[i][j-1];
                } else {
                    table[i][j]=table[i-1][j];
                }
            }
        }
    }

    std::string result = table[m][n];
    std::cout << "Largest common subsequence (PD): " << result << std::endl
              << "Length: " << result.size()              << std::endl;
}

int main(){
    std::string s1= "f34rrfgdruu56";
    std::string s2= "47etyhgfhd5";

    largeCommonSubseqFB(s1,s2);
    largeCommonSubseqPD(s1,s2);
}