// BINARY TREE
// a class oriented binary tree implementation that features all basic operations. Nodes are allocated
// entirely on the heap.
// valid datatypes include std::size_t, int, double, float.
//
// TIME COMPLEXITY
//

#include <iostream>
#include <memory>

template <typename T>
class Tree
{
  private:
    Tree *root_;
    Tree *child_left_;
    Tree *child_right_;

  public:
    // Constructor
    Tree()
        : root_(std::nullopt), child_left_(std::nullopt),
          child_right_(std::nullopt)
    {
    }

    // basic operations

    void addNode(const T &element)
    {
      if (root_ == std::nullopt)
      {
        // we are at the trees root node
      }
    }
};

int main() { return 0; }
