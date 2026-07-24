// STATIC STACK
// stack data-structure with fixed compile-time capacity. Fully stack allocated
// with no dynamic heap allocations. Features basic stack operations.
//
// TIME COMPLEXITY
//  top()             -> O(1)
//  push()            -> O(1)
//  pop()             -> O(1)
//  empty()           -> O(1)
//  clear()           -> O(1)
//  capacity()        -> O(1)
//  reachedCapacity() -> O(1)
//  size()            -> O(1)
//

#include <iostream>

// max fallback capacity
const constexpr std::size_t MAX_CAPACITY = 100;

template <typename T, std::size_t Capacity = MAX_CAPACITY> class Stack
{
  private:
    // members
    T arr_[Capacity];
    std::size_t size_;

  public:
    /// ---------------------------------------------------------------------------------------------------------------
    /**
     * @brief Constructor.
     */
    Stack() : size_(0) {}

    /**
     * @brief Copy constructor.
     */
    Stack(const Stack &) = default;

    /**
     * @brief Move constructor.
     */
    Stack(Stack &&) = default;

    /**
     * @brief Copy assignment operator.
     */
    Stack &operator=(const Stack &) = default;

    /**
     * @brief Move assignment operator.
     */
    Stack &operator=(Stack &&) = default;

    /// ---------------------------------------------------------------------------------------------------------------
    // basic operations

    /**
     * @brief Returns a read-only reference version of the top element.
     * @warning User is responsible for avoiding undefined behavior.
     * @return const T& 
     */
    const T &top() const { return arr_[size_ - 1]; }

    /**
     * @brief Returns a non-const reference version of the top element.
     * @warning User is responsible for avoiding undefined behavior.
     * @return T& 
     */
    T &top() { return arr_[size_ - 1]; }

    /**
     * @brief Pushes element on top of stack.
     * @param element 
     */
    void push(const T &element)
    {
      if (reachedCapacity())
      {
        std::cout
            << "ERROR: Maximum capacity reached. Element couldn't be added!\n";
        return;
      }

      arr_[size_] = element;
      ++size_;
    }

    /**
     * @brief Pops last element from stack.
     */
    void pop()
    {
      if (!empty())
      {
        --size_;
        return;
      }

      std::cout << "ERROR: Stack underflow, cannot pop from empty stack!\n";
    }

    /**
     * @brief Returns true if the stack is empty, false otherwise.
     * @return Boolean value
     */
    bool empty() const { return size_ == 0; }

    /**
     * @brief Resets the stack.
     */
    void clear() { size_ = 0; }

    /**
     * @brief Returns the stacks capacity.
     * @return std::size_t 
     */
    std::size_t capacity() const { return Capacity; }

    /**
     * @brief Returns true if capacity limit has been reached, false otherwise.
     * @return True if capacity was reached, false otherwise.
     */
    bool reachedCapacity() const { return size_ == Capacity; }

    /**
     * @brief Returns the current size of the stack.
     * @return std::size_t 
     */
    std::size_t size() const { return size_; }
};

int main()
{
  // initialized new stack
  Stack<int, 3> s;

  // add elements to stack
  s.push(2);
  s.push(4);
  s.push(3);
  s.push(10); // blocked as capacity had been reached

  // pop last element
  s.pop();

  std::cout << s.top() << std::endl; // 4
  std::cout << "size: " << s.size() << std::endl; // 2

  // reset stack
  s.clear();

  // add element
  s.push(6);

  std::cout << s.top() << std::endl; // 6
  std::cout << "size: " << s.size() << std::endl; // 1

  return 0;
}
