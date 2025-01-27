#include <iostream>
#include <vector>


int taskScheduleFB(std::vector<int> &tasks){
    if(tasks.size()==1){
        return tasks[0];
    }
    int timeSum=INT_MAX;
    for(int i=0;i<tasks.size();++i){
        std::vector<int> subVector;
        int k=0;
        for(int j=0;j<tasks.size();++i){
            if(k==i) ++k;
            subVector.push_back(tasks[k++]);
        }
        int timeSum1=taskScheduleFB(subVector);
        timeSum1 += tasks[i];
        if(timeSum1<timeSum){
            timeSum=timeSum1;
        }
    }
    return timeSum;
}
int main(){
    std::vector<int> tasks = {15,8,3,10};
    std::cout << "DIST" << std::endl;
    std::cout << taskScheduleFB(tasks) << std::endl;
}