#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdlib>

template<typename T>
struct Node
{
    T data;
    std::vector<std::unique_ptr<Node<T>>> children;
    Node(T data){
        this.data=data;
    }
};

template<typename T>
struct Tree{
    Node<T> root;
};

int main(){
    
}

void traverseTreeDV(){
    
}

void fillTree(Tree<int> &Tree,int height,int m){
    
}

void fillNode(Node<int>& node,int height,int m,bool hasForcedChild){//esta mmd va a ser complejidad O(n!) XDDDD
    if(height==1) return;//si llega a altura 1, ya no debe tener mas hijos
    srand(time(NULL));
    //para llegar a height minimo uno debe tener un hijo
    int numChild; //num de hijos que va a tener este nodo
    if(hasForcedChild) numChild=rand()%m+1; //de 1 a m
    else numChild=rand()%(m+1);//de 0 a m
    if(numChild==0) return; //0 hijos, se acaba ahi
    for(int i=0;i<numChild;++i){
        int data=rand()%10+1;//valor del 1 al 10
        node.children.push_back(std::make_unique<Node<int>>(new Node<int>(data)));//crea un nodo con ese valor y lo pone en el vector de children
    }
    int forcedChildIndex= rand()%numChild;//al no estar en el nivel 1, minimo uno de los hijos debe tener uno
    for(int i=0;i<numChild;++i){
        if(i==forcedChildIndex) fillNode(*node.children.at(i).get(),height-1,m,true);
        else fillNode(*node.children.at(i).get(),height-1,m,false);
    }  
}
