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

    bool deleteNode(const T &element)
    {
      Tree<T> *target_node = findNode(element);

      if (!target_node)
      {
        std::cout << "Error: Failed to find Node.\n";
        return false;
      }

      std::size_t count = target_node->count_;

      if (count > 1)
      {
        // simply decrease frequency counter
        --count;
        return true;
      }

      if (target_node == this)
      {
        // we do not support the deletion of the root node
        std::cout << "Error: Deleting the trees root node is not allowed.\n";
        return false;
      }

      // delete Node
      // we temporarily store the nodes variables
      std::unique_ptr<Tree<T>> target_child_left =
          target_node->child_left_ ? std::move(target_node->child_left_)
                                   : nullptr;
      std::unique_ptr<Tree<T>> target_child_right =
          target_node->child_left_ ? std::move(target_node->child_left_)
                                   : nullptr;
      Tree<T> *target_root = target_node->root_;

      // determine if our target node is the left or right child of it's root
      bool is_left = false;

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
        std::unique_ptr<Tree<T>> predecessor = std::move(target_child_left);

        while (predecessor->child_right_)
        {
          predecessor = std::move(predecessor->child_right_);
        }

        // we want to replace the target node with it's predecessor
        // if the predecessor has a left child, we want to have
        // this child as the predecessors root's right child
        Tree *predecessor_root = predecessor->root_;

        predecessor->root_ = target_root;
        std::unique_ptr<Tree<T>> predecessor_child_left =
            predecessor->child_right_ ? std::move(predecessor->child_right_)
                                      : nullptr;

        predecessor->child_left_ = std::move(target_child_left);
        predecessor->child_right_ = std::move(target_child_right);

        if (is_left)
        {
          target_root->child_left_ = std::move(predecessor);
        }
        else
        {
          target_root->child_right_ = std::move(predecessor);
        }

        predecessor_root->child_right_ = std::move(predecessor_child_left);
        predecessor_child_left->root_ = predecessor_root;

        return true;
      }

      // case 3: target has just one child
      if (target_child_left)
      {
        if (is_left)
        {
          target_root->child_left_ = std::move(target_child_left);
        }
        else
        {
          target_root->child_right_ = std::move(target_child_left);
        }
      }
      else
      {
        if (is_left)
        {
          target_root->child_left_ = std::move(target_child_right);
        }
        else
        {
          target_root->child_right_ = std::move(target_child_right);
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
  t.addNode(1);
  t.addNode(3);

  t.printTree();

  Tree<int> *node = t.findNode(3);

  std::cout << "Found node with value: " << node->getValue() << "\n";

  if (!node)
  {
    std::cout << "failed to find node\n";
  }

  t.deleteNode(3);

  t.printTree();

  return 0;
}
