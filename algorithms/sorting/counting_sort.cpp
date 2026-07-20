// COUNTING SORT
// implementation of stable counting sort operating on positive values only.
//
// RUNTIME
// n being the number of elements and k representing the range.
//    best-case: O(n + k) -> ultimately sums up to n + k due to having no shortcut.
//    average-case: O(n + k) -> same as stated above.
//    worst-case: O(n + k) -> worst-case being the same as best-case, yet acceptable on specific data sets.
//
// Efficient on arrays whose range of input values is relatively small compared to 
// the number of elements in the array. 
// Therefore often used in radix sort.

#include <iostream>

// fills array with given integer
void fillArrayWith(int arr[], int arr_size, int fill)
{
  for (int i = 0; i < arr_size; i++)
  {
    arr[i] = fill;
  }
}

// a version of counting sort which only operates on positive values and also assumes the range
// starts at 0, therefore not needing to determine the smallest value or having to shift the values.
// (strictly ignoring VLA not being supported by C++)
void countingSort(int arr[], int arr_size)
{
  // find the largest integer in the given array
  int target = 0;

  for (int i = 0; i < arr_size; i++)
  {
    if (arr[i] > target)
    {
      target = arr[i];
    }
  }

  // create a temporary array, initialized with 0 at every index
  int temp_size = target + 1;
  int arr_temp[temp_size];

  // fill array with 0s
  fillArrayWith(arr_temp, temp_size, 0);

  // count number of occurrences
  int num = 0;

  for (int i = 0; i < arr_size; i++)
  {
    num = arr[i];
    arr_temp[num]++;
  }

  // compute prefix sums
  for (int i = 1; i < temp_size; i++)
  {
    arr_temp[i] += arr_temp[i - 1];
  }

  // shift array one index to the right, emitting value on last index
  for (int i = target; i >= 1; i--)
  {
    arr_temp[i] = arr_temp[i - 1];
  }

  // reset value at index 0
  arr_temp[0] = 0;

  // we now have the starting index of each given number
  // we create a copy of our source array
  int arr_copy[arr_size];

  for (int i = 0; i < arr_size; i++)
  {
    arr_copy[i] = arr[i];
  }

  // populate the source array with sorted values using our array copy 
  // as well as information about each starting index 
  for (int i = 0; i < arr_size; i++)
  {
    // get starting index
    int index = arr_temp[arr_copy[i]];

    // add value in correct position
    arr[index] = arr_copy[i];

    // increase position
    arr_temp[arr_copy[i]]++;
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
  // here we have a relatively small range of 0 to 9
  int arr[] = {3, 1, 5, 9, 2, 0, 2, 1, 1, 9, 5, 3};
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  std::cout << "unsorted: ";
  printArray(arr, arr_size);

  countingSort(arr, arr_size);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}