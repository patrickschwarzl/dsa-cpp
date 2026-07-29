// DYNAMIC QUEUE
// a simple dynamic queue implementation that allocates elements dynamically on the heap. All elements are stored on
// the heap. Features basic queue operations.
//
// TIME COMPLEXITY
//  enqueue()          -> O(1) amortized (O(n) during reallocation of elements)
//  dequeue()          -> O(1)
//  shrinkToSize()     -> O(n)
//  front()            -> O(1)
//  back()             -> O(1)
//  empty()            -> O(1)
//  clear()            -> O(n) because of call to shrinkToSize()]
//  capacity()         -> O(1)
//  capacityReached()  -> O(1)
//  size()             -> O(1)
//

#include <iostream>
#include <memory>

const constexpr std::size_t CAPACITY = 3;
const constexpr std::size_t CAPACITY_INTERVAL = 5;

template <typename T>
class Queue
{
  private:
    // members
    std::unique_ptr<T[]> arr_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;

  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor. Initializes empty queue.
    Queue()
        : arr_(std::make_unique<T[]>(CAPACITY)), capacity_(CAPACITY), head_(0),
          tail_(0), size_(0)
    {
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Destructor.
    ~Queue() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor.
    Queue(const Queue &) = delete;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Move constructor.
    Queue(Queue &&) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy assignment operator.
    Queue &operator=(const Queue &) = delete;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Move assignment operator.
    Queue &operator=(Queue &&) = delete;

    /// ---------------------------------------------------------------------------------------------------------------
    // basic operations

    void enqueue(const T &element)
    {
      if (capacityReached())
      {
        // allocate additional memory
        std::size_t capacity = capacity_ + CAPACITY_INTERVAL;

        std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(capacity);

        // copy new elements from source array to new array
        // here we make sure to copy the elements in the correct order
        for (std::size_t i = 0; i < size_; i++)
        {
          std::size_t index = (head_ + i) % capacity_;

          new_arr[i] = std::move(arr_[index]);
        }

        // updated capacity
        capacity_ = capacity;

        // update head_ and tail_
        head_ = 0;
        tail_ = size_ - 1;

        // replace old array
        arr_ = std::move(new_arr);

        // DEBUGGING
        for (std::size_t i = 0; i < size_; i++)
          std::cout << arr_[i] << std::endl;

        std::cout << "INFO: Allocated more size!\n";
      }

      // use modulo approach
      if (size_ != 0)
      {
        tail_ = (tail_ + 1) % capacity_;
      }

      arr_[tail_] = element;
      ++size_;
    }

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

      --size_;

      // use modulo approach
      head_ = (head_ + 1) % capacity_;
    }

    void shrinkToSize()
    {
      std::size_t current_size = size_;
      std::size_t target_capacity = current_size > 0 ? current_size : 1;

      if (target_capacity != capacity_)
      {
        std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(target_capacity);

        // copy new elements from source array to new array
        // here we make sure to copy the elements in the correct order
        for (std::size_t i = 0; i < size_; i++)
        {
          std::size_t index = (head_ + i) % capacity_;

          new_arr[i] = std::move(arr_[index]);
        }

        // updated capacity
        capacity_ = target_capacity;

        // update head_ and tail_
        head_ = 0;
        tail_ = target_capacity - 1;

        // replace old array
        arr_ = std::move(new_arr);
      }
    }

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

    bool capacityReached() const { return size_ == capacity_; }

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
    std::size_t capacity() const { return capacity_; }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Resets the queue state to empty.
    void clear()
    {
      head_ = 0;
      tail_ = 0;
      size_ = 0;

      shrinkToSize();
    }
};

int main()
{
  Queue<int> q;

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

  std::cout << "Current capacity: " << q.capacity() << "\n";

  return 0;
}