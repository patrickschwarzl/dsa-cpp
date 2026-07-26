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
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;

  public:
    Queue() : head_(0), tail_(0), size_(0) {}

    // basic operations
 
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

    void dequeue()
    {
      if (size_ == 0)
        return;

      if (size_ == 1)
      {
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

    bool capacityReached() const { return size_ == Capacity; }

    T &front() { return arr_[head_]; }

    T &back() { return arr_[tail_]; }

    bool empty() const { return size_ == 0; }

    std::size_t size() const { return size_; }

    std::size_t capacity() const { return Capacity; }

    void clear()
    {
      head_ = 0;
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