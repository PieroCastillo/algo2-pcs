#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdlib>

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
    Node(T data, std::vector<std::unique_ptr<Node<T>>> children)
    {
        this->data = data;
        this->children = children;
    }
};

template <typename T>
struct Tree
{
    Node<T> root;
    Tree()
    {

    }
    Tree(Node<T> root)
    {
        this->root = root;
    }
};

void fillNode(Node<int> &node, int height, int m, bool hasForcedChild)
{
    // esta mmd va a ser complejidad O(n!) XDDDD
    if (height == 1)
        return; // si llega a altura 1, ya no debe tener mas hijos
    srand(time(NULL));
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
        srand(time(NULL));
        int data = rand() % 10 + 1;                                 // valor del 1 al 10
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
}

void fillTree(Tree<int> &tree, int height, int m)
{
    int data = rand() % 10 + 1; // valor del 1 al 10
    tree.root = Node<int>(data);
    fillNode(tree.root, height, m, true);
    std::cout << "Arbol lleno uwu" << std::endl;
}

void traverseNodeChildren(Node<int> &node)
{
    if (node.children.empty())
    {
        std::cout << node.data << " - ";
        return;
    }
    for (auto &&nodePointer : node.children)
    {
        
        traverseNodeChildren(*nodePointer);
    }
    std::cout << node.data << " - ";
}

void traverseTreeDV(Tree<int> &tree)
{
    std::cout << "Nodos del arbol: ";
    traverseNodeChildren(tree.root);
    return;
}

int main()
{
    Tree<int> tree=Tree<int>();
    const int height = 4;
    const int m = 3;
    fillTree(tree, height, m);
    /*tree.root=Node(10);
    for (int i = 0; i < 3; ++i)
    {
        int data = i;                                 // valor del 1 al 10
        tree.root.children.push_back(std::make_unique<Node<int>>(data)); // crea un nodo con ese valor y lo pone en el vector de children
    }*/
    traverseNodeChildren(tree.root);
}
