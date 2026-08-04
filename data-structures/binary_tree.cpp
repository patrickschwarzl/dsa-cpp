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
    std::unique_ptr<Tree<T>> root_;
    std::unique_ptr<Tree<T>> child_left_;
    std::unique_ptr<Tree<T>> child_right_;

  public:
    // Constructor
    Tree(const T &element)
        : value_(element), root_(nullptr), child_left_(nullptr),
          child_right_(nullptr)
    {
    }

    // basic operations

    void addNode(const T &element)
    {
      if (element <= value_)
      {
        // left subtree
        if (!child_left_)
        {
          // correct node found, allocate new node and initialize its value
          child_left_ = std::make_unique<Tree<T>>(element);
          child_left_->root_ = std::move(this);
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
          child_right_->root_ = std::move(this);
          return;
        }

        child_right_->addNode(element);
      }
    };

    // prints the tree using preorder traversal
    void printTree() const
    {
      // print current value
      std::cout << value_ << "\n";

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

  return 0;
}
