// DOUBLY LINKED LIST
// a class oriented doubly linked list implementation that features all basic
// operations. Every Node is being allocated on the heap using unique pointers
// for traversing and an additional pointer which points to the Nodes parent.
// Valid datatypes include std::size_t, int, double, float.
//
// TIME COMPLEXITY
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
  Node<int> list(1);

  list.addNode(10);
  list.addNode(20);

  list.printList();

  Node<int> *node = list.findNode(30);
  if (node)
  {
    std::cout << "Found Node with value: " << node->getValue() << "\n";
  }
  else 
  {
    std::cout << "Failed to find Node\n";
  }

  return 0;
}
