// MERGE SORT
// recursive implementation of merge sort.
//
// RUNTIME

#include <iostream>

void mergeSort(int arr[], int arr_size, int lower_bound, int upper_bound)
{
  // nothing to sort
  if (arr_size <= 1)
    return;

  // split the array
  if (arr_size / 2)

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

  // adding lower and upper bound
  mergeSort(arr, arr_size, 0, arr_size - 1);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}