// STATIC QUEUE
// a simple queue implementation that uses an fixed size array under the hood. Everything is stored on
// the stack with zero heap allocations.
//
// TIME COMPLEXITY
//

#include <iostream>

template<typename T, std::size_t Capacity>
class Queue
{
  private:
    T arr_[Capacity];
    std::size_t size_;

  public:
    Queue() : size_(0) {}


    // basic operations

    void enqueue(const T& element)
    {
      if (capacityReached())
      {
        std::cout << "ERROR: Current queues capacity has been reached, cannot enqueue further elements.\n";
        return;
      }

      arr_[size_] = element;
      ++size_;
    }

    bool capacityReached() const
    {
      return size_ == Capacity;
    }

    T &front() const
    {
      return arr_[0];
    }

    T &back() const
   {
    return arr_[size_ - 1];
   } 

   bool empty() const
   {
    return size_ == 0;
   }

   std::size_t size() const
   {
    return size_;
   }

};

int main()
{



  return 0;
}