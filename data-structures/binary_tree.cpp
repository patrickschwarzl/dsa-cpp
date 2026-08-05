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
      else
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

    bool deleteNode(const T &element)
    {
      Tree<T>* node = findNode(element);

      if (!node)
      {
        std::cout << "Error: Failed to find Node.\n";
        return false;
      }

      std::size_t count = node->count_;

      if (count > 1)
      {
        // simply decrease frequency counter
        --count;
        return true;
      }

      if (node.get() == this)
      {
        // we do not support the deletion of the root node
        std::cout << "Error: Deleting the trees root node is not allowed.\n";
        return false;
      }

      // delete Node
      // we temporarily store the nodes variables 
      std::unique_ptr<Tree<T>> target_left_child = node->left_child_ ? std::move(node->left_child_) : nullptr;
      std::unique_ptr<Tree<T>> target_right_child = node->right_child_ ? std::move(node->right_child_) : nullptr;
      Tree<T>* target_root = node->root_;

      // determine if our target node is the left or right child of it's root
      bool is_left = false;

      // we split this process into 3 separate cases.
      // case 1: target has no children
      if (!target_left_child && !target_right_child)
      {
        // simply delete the Node
        if (is_left)
        {
          target_root->child_left_.reset();
        }
        else
        {
          target_root->child_right_.reset();
        }

        return true;
      }

      // case 2: target has a left child + a right child
      if (target_left_child && target_right_child)
      {
        // find the largest value on the left side of the target node
        // TODO

        return true;
      }

      // case 3: target has just one child
      if (target_left_child)
      {
        if (is_left)
        {
          target_root->left_child_ = std::move(target_left_child);
        }
        else
        {
          target_root->right_child_ = std::move(target_left_child);
        }
      }
      else
      {
        if (is_left)
        {
          target_root->left_child_ = std::move(target_right_child);
        }
        else
        {
          target_root->right_child_ = std::move(target_right_child);
        }
      }

      return true;

    }

    Tree<T>* findNode(const T &element) 
    {
      // return current Node
      if (element == value_)
      {
        return this;
      }
      
      // search left branch
      if (child_left_ && element < value_)
      {
        return child_left_->findNode(element);
      }

      // search right branch
      if (child_right_ && element > value_)
      {
        return child_right_->findNode(element);
      }
      
      // failed to find Node, return nullptr as fallback value
      return nullptr;
    }

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

    // getters
    T getValue() const
    {
      return value_;
    }
};

int main()
{
  // initialize tree
  Tree<int> t(2);

  t.addNode(1);
  t.addNode(1);
  t.addNode(3);

  t.printTree();

  Tree<int>* node = t.findNode(3);

  std::cout << node->getValue() << "\n";

  if (!node)
  {
    std::cout << "failed to find node\n";
  }

  return 0;
}
