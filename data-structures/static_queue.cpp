// STATIC QUEUE
// a simple queue implementation that uses an fixed size array under the hood. Everything is stored on
// the stack with zero heap allocations.
//
// TIME COMPLEXITY
//

#include <iostream>

// max fallback capacity
const constexpr std::size_t MAX_CAPACITY = 100;

template <typename T, std::size_t Capacity = MAX_CAPACITY>
class Queue
{
  private:
    // members
    T arr_[Capacity];
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;

  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor. Initializes empty queue.
    Queue() : head_(0), tail_(0), size_(0) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Destructor.
    ~Queue() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor.
    Queue(const Queue &) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Move constructor.
    Queue(Queue &&) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy assignment operator.
    Queue &operator=(const Queue &) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Move assignment operator.
    Queue &operator=(Queue &&) = default;

    /// ---------------------------------------------------------------------------------------------------------------
    // basic operations

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Enqueues an element at the back of the queue.
    /// @param element
    void enqueue(const T &element)
    {
      if (capacityReached())
      {
        std::cout << "ERROR: Current queues capacity has been reached, cannot "
                     "enqueue further elements.\n";
        return;
      }

      // circular increment
      if (tail_ + 1 == Capacity)
        tail_ = 0;
      else if (size_ != 0)
        ++tail_;

      arr_[tail_] = element;
      ++size_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Dequeues the front element from the queue.
    void dequeue()
    {
      if (size_ == 0)
        return;

      if (size_ == 1)
      {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
        return;
      }

      /*    // remove element at arr_[0] and shift array to the left ( HAS RUNTIME OF O(n), WE WANT O(1) )
      for (std::size_t i = 0; i < size_; i++)
      {
        arr_[i] = arr_[i + 1];
      } */

      --size_;

      // circular increment
      if (head_ + 1 == Capacity)
        head_ = 0;
      else
        ++head_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns true if capacity limit has been reached, false otherwise.
    /// @return Boolean value
    bool capacityReached() const { return size_ == Capacity; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a non-const reference version of the front element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return T&
    T &front() { return arr_[head_]; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a non-const reference version of the back element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return T&
    T &back() { return arr_[tail_]; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns true if queue is empty.
    /// @return Boolean value
    bool empty() const { return size_ == 0; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns the current size of the queue.
    /// @return std::size_t
    std::size_t size() const { return size_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Return the queues capacity.
    /// @return std::size_t
    std::size_t capacity() const { return Capacity; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Resets the queue state to empty.
    void clear()
    {
      head_ = 0;
      tail_ = 0;
      size_ = 0;
    }
};

int main()
{

  Queue<int, 3> s;

  s.enqueue(4);

  std::cout << "front: " << s.front() << " back: " << s.back() << "\n";

  std::cout << "size: " << s.size() << "\n";

  s.enqueue(5);

  s.enqueue(7);

  s.enqueue(8);

  std::cout << "front: " << s.front() << " back: " << s.back() << "\n";

  s.dequeue();

  std::cout << "size: " << s.size() << "\n";

  std::cout << "front: " << s.front() << " back: " << s.back() << "\n";

  return 0;
}