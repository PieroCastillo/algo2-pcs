#include <iostream>
#include <string>

void large_common_subseq(std::string s1,std::string s2){

}

/*std::string large_common_subseq_FB(std::string s1,std::string s2){
    int n=s1.size(),m=s2.size();
    std::string largeSub = ""; int nLargeSub=0;
    for(int nSub=1;nSub<=std::min(n,m);++nSub){
        for(int nInd1=0;nInd1<=n-1;++nInd1){
            std::string sub1 = std::string(s,nInd1,nSub);
        }
    }
}*/

int main(){
    std::string s= "pene";
    std::string s1=std::string(s,1,-4);
    std::cout << s1 << std::endl
              << s << std::endl;
}