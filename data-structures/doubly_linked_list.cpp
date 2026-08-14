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

    target_node->child_ = std::make_unique(Node<T>(value));
    target_node->child_->parent_ = this;
  }


  };

int main()
{
  Node<int> List(1);



  return 0;
}
