#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

template<typename T>
struct Node
{
    T data;
    std::vector<std::unique_ptr<Node<T>>> children;
};

