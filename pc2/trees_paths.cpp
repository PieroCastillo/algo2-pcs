#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <queue>
#include <functional>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>

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
};

template <typename T>
struct Tree
{
    Node<T> root;
    Tree()
    {
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
    // std::cout << std::endl << "Arbol lleno uwu" << std::endl;
}

void traverseNodeChildren(Node<int> &node)
{
    for (auto &&nodePointer : node.children)
    {
        traverseNodeChildren(*nodePointer);
    }
}

void traverseTreeDV(Tree<int> &tree)
{
    traverseNodeChildren(tree.root);
}

void traverseTreeFB(Tree<int> &tree)
{
    std::queue<std::reference_wrapper<Node<int>>> toVisit;
    toVisit.push(std::ref(tree.root));

    while (!toVisit.empty())
    {
        auto &node = toVisit.front();
        toVisit.pop();
        for (auto &child : node.get().children)
        {
            toVisit.push(std::ref(*child));
        }
    }
}

void benchmark(int maxHeight, int m, std::ofstream &text)
{
    // max: m=3,h=21; m=2,h=60
    for (int h = 1; h <= maxHeight; ++h)
    {
        std::cout << "(" << m << "," << h << ")" << std::endl;
        std::cout << "break before tree Creation" << std::endl;
        std::unique_ptr<Tree<int>> tree = std::make_unique<Tree<int>>();
        fillTree(*tree, h, m);
        std::cout << "break after tree Creation " << std::endl;

        // execute and measure time for maxSumSubsequence_FB
        auto startTime = std::chrono::high_resolution_clock::now();
        traverseTreeFB(*tree);
        std::cout << "break after FB" << std::endl;
        auto endTime = std::chrono::high_resolution_clock::now();
        auto ellapsedFB = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

        // execute and measure time for maxSumSubsequence_DV
        auto startTime2 = std::chrono::high_resolution_clock::now();
        traverseTreeDV(*tree);
        std::cout << "break after DV" << std::endl;
        auto endTime2 = std::chrono::high_resolution_clock::now();
        auto ellapsedDV = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2);

        text << "(" << m << "," << h << ", " << ellapsedFB.count() << "," << ellapsedDV.count() << ")";
    }
}

// args order: maxHeight, maxM
int main(int argc, char *argv[])
{
    int maxHeight = 6;
    int maxM = 2;
    srand(time(NULL));

    if (argc > 1)
    {
        maxHeight = std::atoi(argv[1]);
        maxM = std::atoi(argv[2]);
    }
    // std::vector<int> items = {1, 3, -5, 4, 0, -1, 2, 4};
    // std::cout << maxSumSubsequence_FB(items) << std::endl;
    // std::cout << maxSumSubsequence_DV(items) << std::endl;

    std::string fileName = "tree_paths_stats.txt";
    std::ofstream file(fileName);

    // std::stringstream stream;

    file.clear();
    benchmark(60, 2, file);
    file << std::endl;
    benchmark(21,3, file);
    file.close();

    return 0;
}
