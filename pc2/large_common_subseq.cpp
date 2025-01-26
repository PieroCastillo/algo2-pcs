#include <iostream>
#include <string>

std::string large_common_subseq_FBH(std::string &s1,std::string &s2,int m, int n){
    if(m==0||n==0){
        return "";
    }
    if(s1[m-1]==s2[n-1]){
        std::string result=large_common_subseq_FBH(s1,s2,m-1,n-1);
        result.push_back(s1[m-1]);
        return result;
    } else {
        std::string result1=large_common_subseq_FBH(s1,s2,m-1,n);
        std::string result2=large_common_subseq_FBH(s1,s2,m,n-1);
        if(result1.size()<result2.size()){
            return result2;
        } else {
            return result1;
        }
    }
}


void large_common_subseq_FB(std::string s1,std::string s2){
    std::string result = large_common_subseq_FBH(s1,s2,s1.size(),s2.size());
    std::cout << "Largest common subsequence: " << result << std::endl
              << "Length: " << result.size()              << std::endl;
}


int main(){
    std::string s1= "fiuldhsnvgdg";
    std::string s2= "asdfuoasojf";

    large_common_subseq_FB(s1,s2);
}