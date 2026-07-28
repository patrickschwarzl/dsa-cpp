// STATIC QUEUE
// a simple queue implementation that uses an fixed size array under the hood. Everything is stored on
// the stack with zero heap allocations.
//
// TIME COMPLEXITY
//  enqueue()          -> O(1)
//  dequeue()          -> O(1)
//  front()            -> O(1)
//  back()             -> O(1)
//  empty()            -> O(1)
//  clear()            -> O(1)
//  capacity()         -> O(1)
//  capacityReached()  -> O(1)
//  size()             -> O(1)
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
      // this does work and replaces the need of modulo
      // it's a design choice and I might add the modulo 
      // version in the near future as well
      // same applies to dequeue()
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
    /// @brief Returns a read-only reference version of the front element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return const T&
    const T &front() const { return arr_[head_]; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a non-const reference version of the front element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return T&
    T &front() { return arr_[head_]; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Returns a read-only reference version of the back element.
    /// @warning User is responsible for avoiding undefined behavior.
    /// @return const T&
    const T &back() const { return arr_[tail_]; }

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
  Queue<int, 3> q;

  q.enqueue(10);
  q.enqueue(20);
  q.enqueue(30);

  std::cout << "Front: " << q.front() << " | Back: " << q.back()
            << " | Size: " << q.size() << "\n";

  q.enqueue(40); // trigger circular increment

  q.dequeue();
  q.enqueue(40);

  std::cout << "Front: " << q.front() << " | Back: " << q.back()
            << " | Size: " << q.size() << "\n";

  q.clear();
  std::cout << "Empty? " << (q.empty() ? "Yes" : "No")
            << " | Size: " << q.size() << "\n";

  return 0;
}