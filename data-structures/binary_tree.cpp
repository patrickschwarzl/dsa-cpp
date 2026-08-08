// BINARY TREE
// a class oriented binary tree implementation that features all basic
// operations. Nodes are allocated entirely on the heap. It also features a
// frequency count to handle duplicate values instead of allocating multiple
// nodes with the same value. valid datatypes include std::size_t, int, double,
// float.
//
// TIME COMPLEXITY
//

#include <iostream>
#include <memory>

template <typename T>
class Tree
{
  private:
    T value_;
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
        // element with same value already exists, therefore we just increase it's
        // count
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

    // previous attempt involved trying to swap nodes, yet due to many design limitations, I decided to switch
    // just the nodes values instead.
    bool deleteNode(const T &element)
    {
      Tree<T> *target_node = findNode(element);

      if (!target_node)
      {
        std::cout << "Error: Failed to find Node.\n";
        return false;
      }

      if (target_node->count_ > 1)
      {
        // simply decrease frequency counter
        --target_node->count_;
        return true;
      }

      // we retrieve information about the target nodes current relations
      Tree<T> *target_child_left =
          target_node->child_left_ ? target_node->child_left_.get() : nullptr;
      Tree<T> *target_child_right =
          target_node->child_right_ ? target_node->child_right_.get() : nullptr;
      Tree<T> *target_root = target_node->root_;

      // determine if our target node is the left or right child of it's root
      bool is_left = false;

      if (target_root->child_left_.get() == target_node)
      {
        is_left = true;
      }

      // we split this process into 3 separate cases.
      // case 1: target has no children
      if (!target_child_left && !target_child_right)
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
      if (target_child_left && target_child_right)
      {
        // find predecessor of target node
        Tree<T> *predecessor_ptr = target_child_left;

        while (predecessor_ptr->child_right_)
        {
          predecessor_ptr = predecessor_ptr->child_right_.get();
        }

        // we want to replace the target node's with the value of it's predecessor, therefore we dont have
        // to switch the nodes itself, but rather just swap their values
        // declare predecessors value as the target nodes value
        target_node->value_ = predecessor_ptr->value_;
        target_node->count_ = predecessor_ptr->count_;

        // set the predecessors count to 1, so the it gets wiped out by the recursive call to deleteNode()
        predecessor_ptr->count_ = 1;

        // recursive call starting from the original targets left child
        return target_node->child_left_->deleteNode(predecessor_ptr->value_);
      }

      // case 3: target has just one child
      if (target_child_left)
      {
        if (is_left)
        {
          target_root->child_left_ = std::move(target_node->child_left_);
          target_node->child_left_->root_ = target_root->child_left_.get();
        }
        else
        {
          target_root->child_right_ = std::move(target_node->child_left_);
          target_node->child_right_->root_ = target_root->child_left_.get();
        }
      }
      else
      {
        if (is_left)
        {
          target_root->child_left_ = std::move(target_node->child_right_);
          target_node->child_left_->root_ = target_root->child_right_.get();
        }
        else
        {
          target_root->child_right_ = std::move(target_node->child_right_);
          target_node->child_right_->root_ = target_root->child_right_.get();
        }
      }

      return true;
    }

    Tree<T> *findNode(const T &element)
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
    T getValue() const { return value_; }
};

int main()
{
  // initialize tree
  Tree<int> t(2);

  t.addNode(1);
  t.addNode(5);
  t.addNode(8);
  t.addNode(4);
  t.addNode(3);

  t.printTree();

  Tree<int> *node = t.findNode(3);

  std::cout << "Found node with value: " << node->getValue() << "\n";

  if (!node)
  {
    std::cout << "failed to find node\n";
  }

  t.deleteNode(5);

  t.printTree();

  return 0;
}
