// INSERTION SORT
// default implementation of insertion sort.
// 
// RUNTIME
//    best-case: O(n) -> array was already sorted.
//    average-case: O(n^2) -> array has random order of elements.
//    worst-case: O(n^2) -> array was initialized in reverse order.
//

#include <iostream>

// This version was done from scratch and has the same runtime as the typical textbook approach,
// yet uses 3 operations instead of only one. Reason for that is the way I swap the elements (line 28-30).
// The better solution is to switch the elements to the right, then insert x.
/* void insertionSort(int arr[], int arr_size)
{
  // keeping track of progress
  int unsorted = 1;

  // nothing to sort
  if (arr_size <= 1)
    return;

  do
  {
    int x = unsorted; // x being the element we wish to insert
    int temp = 0;

    // compare to sorted integers (integers to the left of x)
    for (int sorted = unsorted - 1; sorted >= 0; --sorted)
    {
      if (arr[sorted] > arr[x])
      {
        // swap
        temp = arr[sorted];
        arr[sorted] = arr[x];
        arr[x] = temp;

        // update position
        x--;
      }
      else
        break;
    }

    // move on to next element
    unsorted++;

  } while (unsorted < arr_size);
} */

// reworked version of my previous insertion sort attempt, now shifting elements and inserting x in the gap.
// I removed the outer while-loop and used an inner while-loop to handle the shifting logic. Took some time but
// eventually got it to work.
void insertionSort(int arr[], std::size_t arr_size)
{
  // nothing to sort
  if (arr_size <= 1)
    return;

  for (int unsorted = 1; unsorted < static_cast<int>(arr_size); ++unsorted)
  {
    int x = arr[unsorted]; // storing target element to safely shift array
    int sorted = unsorted - 1;

    while (sorted >= 0 && arr[sorted] > x)
    {
      // shift elements to the right to make space for insertion
      arr[sorted + 1] = arr[sorted];
      --sorted;
    }

    // insert x into the gap
    arr[sorted + 1] = x;
  }
}

void printArray(const int arr[], std::size_t arr_size)
{
  for (std::size_t i = 0; i < arr_size; ++i)
  {
    std::cout << arr[i] << " ";
  }

  std::cout << std::endl;
}

int main()
{
  int arr[] = {5, 2, 4, 9, -2, 13, 1, 3, 100, 232, 67, 50, 0, 3, -40, -10, 20};
  std::size_t arr_size = sizeof(arr) / sizeof(arr[0]);

  std::cout << "unsorted: ";
  printArray(arr, arr_size);

  insertionSort(arr, arr_size);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}
