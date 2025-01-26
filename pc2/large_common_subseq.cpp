#include <iostream>
#include <string>

void large_common_subseq_FB(std::string s1,std::string s2){
    
}

std::pair<std::string,int> large_common_subseq_FBH(std::string &s1,std::string &s2,std::string maxSub,int m, int n){
    if(m==0||n==0){
        return {"",0};
    }
    if(s1[m-1]==s2[n-1]){
        std::pair<std::string,int> result=large_common_subseq_FBH(s1,s2,maxSub,m-1,n-1);
        maxSub.push_back(s1[m-1]); std::get<1>(result)+=1;
        return result;
    } else {
        std::pair<std::string,int> result1=large_common_subseq_FBH(s1,s2,maxSub,m-1,n);
        std::pair<std::string,int> result2=large_common_subseq_FBH(s1,s2,maxSub,m,n-1);
        if(std::get<1>(result1)<std::get<1>(result2)){
            return result2;
        } else {
            return result1;
        }
    }
}

int main(){
    std::string s= "pene";
    std::string s1=std::string(s,1,-4);
    std::cout << s1 << std::endl
              << s << std::endl;
}