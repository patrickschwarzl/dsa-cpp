// DYNAMIC STACK
// stack data-structure which allocates elements dynamically on the heap. Fully
// heap allocated and features basic stack operations.
//
// TIME COMPLEXITY
//  top()             -> O(1)
//  push()            -> O(1) amortized | O(n) in worst-case
//  pop()             -> O(1)
//  empty()           -> O(1)
//  clear()           -> O(1)
//  capacity()        -> O(1)
//  reachedCapacity() -> O(1)
//  size()            -> O(1)
//  shrinkToSize()    -> O(n)
//

#include <iostream>
#include <memory>
#include <optional>

const constexpr std::size_t CAPACITY = 10;
const constexpr std::size_t CAPACITY_INTERVAL = 5;

template <typename T> class Stack
{
  private:
    std::unique_ptr<T[]> arr_;
    std::size_t capacity_;
    std::optional<std::size_t> index_;

  public:
    // Constructor
    Stack()
        : arr_(std::make_unique<T[]>(CAPACITY)), capacity_(CAPACITY),
          index_(std::nullopt)
    {
    }

    // Destructor, although the arr_ memory block is freed by the unique
    // pointer.
    ~Stack() = default;

    /**
     * @brief Move constructor.
     */
    Stack(Stack &&) = default;

    /**
     * @brief Copy assignment operator.
     */
    Stack &operator=(const Stack &) = delete;

    /**
     * @brief Move assignment operator.
     */
    Stack &operator=(Stack &&) = delete;

    // basic operations

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns the stacks current size.
    /// @return std::size_t
    std::size_t size() const { return index_.has_value() ? *index_ + 1 : 0; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Pushes element on top of stack.
    /// @param element
    void push(const T &element)
    {
      if (!index_.has_value())
        index_ = 0;
      else
        (*index_)++;

      // check if additional memory needs to be allocated
      if (*index_ >= capacity_)
      {
        capacity_ += CAPACITY_INTERVAL;

        // allocate new memory
        std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(capacity_);

        // safely move elements from source array into the new array
        for (std::size_t i = 0; i < *index_; i++)
        {
          new_arr[i] = std::move(arr_[i]);
        }

        // replace the old array with the new one
        arr_ = std::move(new_arr);

        std::cout << "INFO: Allocated more size!\n";
      }

      arr_[*index_] = element;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Pops last element from stack.
    void pop()
    {
      if (index_.has_value())
      {
        if (*index_ == 0)
          index_ = std::nullopt;
        else
          --(*index_);

        return;
      }

      std::cout << "ERROR: Stack underflow, cannot pop from empty stack!\n";
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Shrink the stack to it's current size.
    void shrinkToSize()
    {
      std::size_t current_size = size();
      std::size_t target_capacity = current_size > 0 ? current_size : 1;

      if (target_capacity != capacity_)
      {
        // allocate new memory
        std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(target_capacity);
        capacity_ = target_capacity;

        // safely move elements from source array into the new array
        for (std::size_t i = 0; i < current_size; i++)
        {
          new_arr[i] = std::move(arr_[i]);
        }

        // replace the old array with the new one
        arr_ = std::move(new_arr);
      }
      else
      {
        std::cout << "INFO: Stack already has optimal size!\n";
      }
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns true if stack is empty.
    /// @return Boolean value
    bool empty() const { return !index_.has_value(); }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns the array to its default state, empty and default capacity.
    void clear()
    {
      // reset the stacks capacity to default
      arr_ = std::make_unique<T[]>(CAPACITY);
      capacity_ = CAPACITY;

      index_ = std::nullopt;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Return the stacks current capacity.
    /// @return std::size_t
    std::size_t capacity() const { return capacity_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns true if capacity is reached, false otherwise.
    /// @return Boolean value
    bool reachedCapacity() const { return (size() == capacity_); }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a read-only reference version of the top element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return const T&
    const T &top() const { return arr_[index_.value()]; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a non-const reference version of the top element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return T&
    T &top() { return arr_[index_.value()]; }
};

int main()
{
  Stack<int> s;

  s.push(5);
  s.push(3);

  std::cout << s.top() << "\n";

  s.pop();

  std::cout << s.top() << "\n";
  std::cout << "size: " << s.size() << "\n";

  s.shrinkToSize();
  s.push(10);

  std::cout << "size: " << s.size() << "\n";
  std::cout << s.top() << "\n";

  s.clear();

  std::cout << "size: " << s.size() << "\n";
  std::cout << "capacity: " << s.capacity() << "\n";

  return 0;
}
