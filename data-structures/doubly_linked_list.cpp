// DOUBLY LINKED LIST
// a class oriented doubly linked list implementation that features all basic
// operations. Every Node is being allocated on the heap using unique pointers
// for traversing and an additional pointer which points to the Nodes parent.
// Valid datatypes include std::size_t, int, double, float.
//
// TIME COMPLEXITY
//  addNode()    -> O(n)
//  deleteNode() -> O(n)
//  findNode()   -> O(n)
//  printList()  -> O(n)
//  getValue()   -> O(1)
//

#include <iostream>
#include <memory>

template <typename T>
class Node
{
  // members
  private:
    T value_;
    Node<T> *parent_;
    std::unique_ptr<Node<T>> child_;

  public:
    // constructor
    Node(const T &value) : value_(value), parent_(nullptr), child_(nullptr) {}

    // basic operations
    void addNode(const T &value)
    {
      Node *target_node = this;

      while (target_node->child_)
      {
        target_node = target_node->child_.get();
      }

      target_node->child_ = std::make_unique<Node<T>>(value);
      target_node->child_->parent_ = this;
    }

    // deletes first Node of specified value
    bool deleteNode(const T &value)
    {
      Node<T> *target_node = findNode(value);

      if (!target_node)
      {
        return false;
      }

      Node<T> *parent = target_node->parent_;
      std::unique_ptr<Node<T>> child = std::move(target_node->child_);

      // target node is also root, special case
      if (!parent)
      {
        if (!child)
        {
          std::cout << "Error: Cannot delete final remaining node.\n";
          return false;
        }

        // swap value of root with value of it's child, initialize child
        // as the new root
        value_ = child->value_;

        // retrieve child of child
        child_ = std::move(child->child_);

        if (child_)
        {
          child_->parent_ = this;
        }

        return true;
      }

      parent->child_ = std::move(child);

      if (parent->child_)
      {
        parent->child_->parent_ = parent;
      }

      return true;
    }

    Node *findNode(const T &value)
    {
      Node<T> *target_node = this;

      if (value == value_)
      {
        return target_node;
      }

      // indicates last child
      if (!target_node->child_)
      {
        return nullptr;
      }

      return target_node->child_->findNode(value);
    }

    void printList()
    {
      Node<T> *target_node = this;

      std::cout << "Value: " << target_node->value_ << "\n";

      if (target_node->child_)
      {
        target_node->child_->printList();
      }
    }

    T getValue() const { return value_; }
};

int main()
{
  // TESTING

  Node<int> list(10);
  list.addNode(5);
  list.addNode(15);
  list.addNode(2);
  list.addNode(7);
  list.addNode(12);
  list.addNode(20);
  list.addNode(14);

  list.printList();

  // deleting missing node
  if (list.deleteNode(99))
  {
    std::cout << "FAIL\n";
  }
  else
  {
    std::cout << "PASS\n";
  }

  // deleting leaf node
  list.deleteNode(14);
  if (list.findNode(14) == nullptr)
  {
    std::cout << "PASS\n";
  }
  else
  {
    std::cout << "FAIL\n";
  }

  // delete regular node
  list.deleteNode(7);
  if (list.findNode(7) == nullptr)
  {
    std::cout << "PASS\n";
  }
  else
  {
    std::cout << "FAIL\n";
  }

  list.printList();

  // delete root node
  list.deleteNode(10);
  if (list.findNode(10) == nullptr)
  {
    std::cout << "PASS\n";
  }
  else
  {
    std::cout << "FAIL\n";
  }

  list.printList();

  return 0;
}
