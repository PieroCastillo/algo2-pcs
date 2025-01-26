#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <queue>
#include <functional>

template <typename T>
struct Node
{
    T data;
    std::vector<std::unique_ptr<Node<T>>> children;
    Node()
    {
    }
    Node(T data)
    {
        this->data = data;
    }
    void check()
    {
        if (children.size() > 2)
            std::cout << std::endl
                      << data << std::endl
                      << std::endl;
        // std::cout << std::endl << "ALERTA DE CURIFEO ALIAS DATA: " << data << std::endl<< std::endl;
    }
};

template <typename T>
struct Tree
{
    Node<T> root;
    Tree()
    {
    }

    void printTree()
    {
        printTreeH(root, "");
    }

    void printTreeH(Node<int> &node, std::string prefix)
    {
        std::cout << prefix << node.data << std::endl;
        if (node.children.empty())
            return;
        for (auto &&nodePointer : node.children)
        {
            printTreeH(*nodePointer, prefix + "|\t");
        }
    }
};

void fillNode(Node<int> &node, int height, int m, bool hasForcedChild)
{
    // esta mmd va a ser complejidad O(n!) XDDDD
    if (height == 1)
        return; // si llega a altura 1, ya no debe tener mas hijos

    // para llegar a height minimo uno debe tener un hijo
    int numChild; // num de hijos que va a tener este nodo
    if (hasForcedChild)
    {
        numChild = rand() % m + 1; // de 1 a m
    }
    else
    {
        numChild = rand() % (m + 1); // de 0 a m
    }
    if (numChild == 0)
        return; // 0 hijos, se acaba ahi
    for (int i = 0; i < numChild; ++i)
    {
        int data = rand() % 40 + 1;                                 // valor del 1 al 10
        node.children.push_back(std::make_unique<Node<int>>(data)); // crea un nodo con ese valor y lo pone en el vector de children
    }
    int forcedChildIndex = rand() % numChild; // al no estar en el nivel 1, minimo uno de los hijos debe tener uno
    for (int i = 0; i < numChild; ++i)
    {
        if (i == forcedChildIndex)
        {
            fillNode(*node.children.at(i).get(), height - 1, m, true);
        }
        else
        {
            fillNode(*node.children.at(i).get(), height - 1, m, false);
        }
    }
    // node.check();
}

void fillTree(Tree<int> &tree, int height, int m)
{
    int data = rand() % 40 + 1; // valor del 1 al 10
    tree.root = Node<int>(data);
    fillNode(tree.root, height, m, true);
    //std::cout << std::endl << "Arbol lleno uwu" << std::endl;
}

void traverseNodeChildren(Node<int> &node, int &counter)
{
    counter++;
    //std::cout << node.data << " - ";
    for (auto &&nodePointer : node.children)
    {
        traverseNodeChildren(*nodePointer, counter);
    }
}

void traverseTreeDV(Tree<int> &tree)
{
    //std::cout << "Nodos del arbol: ";
    int counter = 0;
    traverseNodeChildren(tree.root, counter);
    std::cout << "Hay " << counter << " nodos" << std::endl;
}

void traverseTreeFB(Tree<int> &tree)
{
    int counter = 0;
    std::queue<std::reference_wrapper<Node<int>>> toVisit;
    toVisit.push(std::ref(tree.root));

    while (!toVisit.empty())
    {
        counter++;
        auto &node = toVisit.front();
        // Do something
        //std::cout << node.get().data << std::endl;
        toVisit.pop();
        for (auto &child : node.get().children)
        {
            toVisit.push(std::ref(*child));
        }
    }
    std::cout << "Hay " << counter << " nodos" << std::endl;
}

int main()
{

    const int height = 6;
    const int m = 2;
    srand(time(NULL));
    for (int i = 0; i < 4; ++i)
    {
        Tree<int> tree = Tree<int>();
        fillTree(tree, height, m);
        /*tree.root=Node(10);
        for (int i = 0; i < 3; ++i)
        {
            int data = i;                                 // valor del 1 al 10
            tree.root.children.push_back(std::make_unique<Node<int>>(data)); // crea un nodo con ese valor y lo pone en el vector de children
        }*/
        //tree.printTree();
        traverseTreeDV(tree);
        traverseTreeFB(tree);
    }
}
