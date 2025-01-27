#include <iostream>
#include <vector>


int taskScheduleFB(std::vector<int> tasks, int currSum){
    if(tasks.size()==1){
        return currSum + tasks[0];
    }
    int timeSum=INT_MAX;
    for(int i=0;i<tasks.size();++i){
        std::vector<int> subVector;
        int k=0;
        for(int j=0;j<tasks.size()-1;++j){
            if(k==i) ++k;
            subVector.push_back(tasks[k++]);
        }
        currSum += tasks[i];
        int timeSum1=taskScheduleFB(subVector,currSum)+currSum;
        
        if(timeSum1<timeSum){
            timeSum=timeSum1;
        }
    }
    return timeSum;
}
int main(){
    std::vector<int> tasks = {15,8,3,10};
    std::cout << "DIST" << std::endl;
    std::cout << taskScheduleFB(tasks,0) << std::endl;
}