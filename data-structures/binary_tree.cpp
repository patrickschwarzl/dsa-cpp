// BINARY TREE
// a class oriented binary tree implementation that features all basic operations. Nodes are allocated
// entirely on the heap. It also features a frequency count to handle duplicate values instead of allocating
// multiple nodes with the same value.
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
    std::size_t count_;
    Tree<T> *root_;
    std::unique_ptr<Tree<T>> child_left_;
    std::unique_ptr<Tree<T>> child_right_;

  public:
    // Constructor
    Tree(const T &element)
        : value_(element), count_(1), root_(nullptr), child_left_(nullptr),
          child_right_(nullptr)
    {
    }

    // basic operations

    void addNode(const T &element)
    {
      if (element == value_)
      {
        // element with same value already exists, therefore we just increase it's count
        count_++;
        return;
      }
      else if (element < value_)
      {
        // left subtree
        if (!child_left_)
        {
          // correct node found, allocate new node and initialize its value
          child_left_ = std::make_unique<Tree<T>>(element);
          child_left_->root_ = this;
          return;
        }

        child_left_->addNode(element);
      }
      else if (element > value_)
      {
        // right subtree
        if (!child_right_)
        {
          child_right_ = std::make_unique<Tree<T>>(element);
          child_right_->root_ = this;
          return;
        }

        child_right_->addNode(element);
      }
    };

    std::unique_ptr<Tree<T>> findNode(const T &element) {}

    // prints the tree using preorder traversal
    void printTree() const
    {
      // print current value, possible also duplicates
      for (std::size_t i = 0; i < count_; i++)
      {
        std::cout << value_ << "\n";
      }

      // if exists, recursive call on left child
      if (child_left_)
        child_left_->printTree();

      // else try the right side
      if (child_right_)
        child_right_->printTree();
    }
};

int main()
{
  // initialize tree
  Tree<int> t(2);

  t.printTree();

  t.addNode(1);
  t.addNode(1);

  t.printTree();

  return 0;
}
