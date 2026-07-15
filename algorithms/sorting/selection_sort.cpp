// SELECTION SORT
//
// RUNTIME
//    best-case: O(n^2) -> even if the array is sorted, we still have to scan the remaining unsorted elements.
//    average-case: O(n^2) -> average case is quadratic time also.
//    worst-case: O(n^2) -> initial array order doesn't matter, we still compare each element.
//

#include <iostream>

// My first and final attempt to code the selection sort algorithm.
// It works as expected and uses two nested for-loops which results in O(n^2), quadratic time complexity.
void selectionSort(int arr[], int arr_size)
{
  // nothing to sort
  if (arr_size <= 1)
    return;

  for (int sorted = 0; sorted < arr_size; sorted++)
  {
    // set element at sorted as the smallest found integer
    int target_index = sorted;
    int temp = 0;

    // go from the end of the array up to the sorted portion of the array
    for (int unsorted = arr_size - 1; unsorted > sorted; unsorted--)
    {
      if (arr[unsorted] < arr[target_index])
      {
        target_index = unsorted;
      }
    }

    // check if a smaller number than arr[sorted] was found
    if (target_index != sorted)
    {
      // swap elements
      temp = arr[sorted];
      arr[sorted] = arr[target_index];
      arr[target_index] = temp;
    }
  }
}

void printArray(const int arr[], int arr_size)
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
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  std::cout << "unsorted: ";
  printArray(arr, arr_size);

  selectionSort(arr, arr_size);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}
