// STATIC QUEUE
// a simple queue implementation that uses an fixed size array under the hood. Everything is stored on
// the stack with zero heap allocations.
//
// TIME COMPLEXITY
//

#include <iostream>

template <typename T, std::size_t Capacity> class Queue
{
  private:
    T arr_[Capacity];
    std::size_t size_;

  public:
    Queue() : size_(0) {}

    // basic operations

    void enqueue(const T &element)
    {
      if (capacityReached())
      {
        std::cout << "ERROR: Current queues capacity has been reached, cannot "
                     "enqueue further elements.\n";
        return;
      }

      arr_[size_] = element;
      ++size_;
    }

    void dequeue()
    {
      if (size_ == 0)
        return;

      if (size_ == 1)
        size_ = 0;

      // remove element at arr_[0] and shift array to the left
      for (std::size_t i = 0; i < size_; i++)
      {
        arr_[i] = arr_[i + 1];
      }

      --size_;
    }

    bool capacityReached() const { return size_ == Capacity; }

    T &front() { return arr_[0]; }

    T &back() { return arr_[size_ - 1]; }

    bool empty() const { return size_ == 0; }

    std::size_t size() const { return size_; }

    std::size_t capacity() const { return Capacity; }

    void clear() { size_ = 0; }
};

int main()
{

  Queue<int, 3> s;

  s.enqueue(4);

  std::cout << "front: " << s.front() << " back: " << s.back() << "\n";

  std::cout << "size: " << s.size() << "\n";

  s.enqueue(5);

  std::cout << "front: " << s.front() << " back: " << s.back() << "\n";

  s.dequeue();

  std::cout << "size: " << s.size() << "\n";

  std::cout << "front: " << s.front() << " back: " << s.back() << "\n";

  return 0;
}