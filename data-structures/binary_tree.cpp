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
    const T value_;
    Tree *root_;
    Tree *child_left_;
    Tree *child_right_;

  public:
    // Constructor
    Tree(const T &element)
        : value_(element), root_(std::nullopt), child_left_(std::nullopt),
          child_right_(std::nullopt)
    {
    }

    // basic operations

    void addNode(const T &element)
    {
      if (element <= value_)
      {
        // left subtree
        if (child_left_ == std::nullopt)
        {
          // correct node found, allocate new node and initialize its value
          child_left_ = new Tree(element);
          return;
        }

        child_left_->addNode(element);
      }
      else if (element > value_)
      {
        // right subtree
        if (child_right_ == std::nullopt)
        {
          child_right_ = new Tree(element);
          return;
        }

        child_right_->addNode(element);
      }
    };

    // prints the tree, root -> left child -> right child
    void printTree() 
    {
      if (root_ == std::nullopt)
        return;

      // print root node's value
      std::cout << 
    }
}

int main()
{
  return 0;
}
