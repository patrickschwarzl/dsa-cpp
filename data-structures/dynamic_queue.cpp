// STATIC QUEUE
// a simple dynamic queue implementation that allocates elements dynamically on the heap. All elements are stored on
// the heap. Features basic queue operations.
//
// TIME COMPLEXITY
//

#include <iostream>
#include <memory>

const constexpr std::size_t CAPACITY = 10;
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
    Queue() : arr_(std::make_unique<T[]>(CAPACITY)), capacity_(CAPACITY), head_(0), tail_(0), size_(0) {}

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
    Queue &operator=(const Queue &) = delete;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Move assignment operator.
    Queue &operator=(Queue &&) = delete;

    /// ---------------------------------------------------------------------------------------------------------------
    // basic operations


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