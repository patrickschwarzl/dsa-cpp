// STATIC STACK
// stack data-structure with fixed compile-time capacity. Fully stack allocated 
// with no dynamic heap allocations.

#include <iostream>

// max fallback capacity
const constexpr std::size_t MAX_CAPACITY = 100;

template <typename T, std::size_t Capacity = MAX_CAPACITY>
class Stack
{
  private:
    // members
    T arr_[Capacity];
    std::size_t size_;
    bool capacity_reached_;

    // private methods
    const bool checkCapacity()
    {
      if (size_ >= Capacity)
      {
        capacity_reached_ = true;
        return false;
      }

      capacity_reached_ = false;
      return true;
    }

    void increaseSize()
    {
      size_++;
      checkCapacity();
    }

  public:
    // constructor
    Stack() : size_(0), capacity_reached_(false) {}

    // basic operations

    // @brief returns top element
    // user is responsible for undefined behavior
    const T &top() const
    {
      return arr_[size_ - 1];
    }

    // @brief non-const version, returns top element
    T &top()
    {
      return arr_[size_ - 1];
    }

    // pushes element into stack
    void push(const T &element)
    {
      if (!checkCapacity())
      {
        std::cout << "ERROR: Maximum capacity reached. Element couldn't be added!" << std::endl;
        return;
      }

      arr_[size_] = element;
      increaseSize();
    }
};

int main()
{
  Stack<int, 20> s;

  s.push(2);
  s.push(4);

  std::cout << s.top() << std::endl;

  return 0;
}