// DYNAMIC STACK
// stack data-structure which allocates elements dynamically on the heap. Fully
// heap allocated and features basic stack operations.
//
// TIME COMPLEXITY
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
        arr_ = std::make_unique<T[]>(capacity_);
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

  return 0;
}