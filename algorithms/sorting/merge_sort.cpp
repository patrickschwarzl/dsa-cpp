// MERGE SORT
// recursive implementation of merge sort, using virtual array splitting (lower bound, upper bound).
//
// RUNTIME
//    best-case: O(n log n) -> unfortunately, the algorithm still has to undergo every split and merge.
//    average-case: O(n log n) -> same reason as stated above.
//    worst-case: O(n log n) -> total work still sums up to n log n.
//

// Took me quite a lot of time to design the recursive approach and also debug everything, especially the bounds 
// inside merge() caused a lot of trouble.
// Overall very interesting algorithm, although my version makes it seem unnecessarily complex, it really isn't.

#include <iostream>

// helper function that creates two temporary arrays and correctly merges those
void merge(int arr[], int lower_bound, int middle_index, int upper_bound)
{
  // use information given to create two temporary arrays
  int left_size = middle_index - lower_bound + 1;
  int right_size = upper_bound - middle_index;

  int arr_left[left_size];
  int arr_right[right_size];
  
  // copy elements on the left side into arr_left
  for (int i = lower_bound; i <= middle_index; i++)
  {
    // we shift to the left which allows us to start at index 0
    int shift_left = i - lower_bound;
    arr_left[shift_left] = arr[i];
  }

  // copy elements on the right side into arr_right
  for (int i = middle_index + 1; i <= upper_bound; i++)
  {
    int shift_left = i - (middle_index + 1);
    arr_right[shift_left] = arr[i];
  }

  int left_index = 0;
  int right_index = 0;
  int source_index = lower_bound; // lower_bound will always represent the first element in the source array
                                  // that we want to be initialized next

  // decided on one while-loop instead of multiple for-loops
  while (left_index < left_size && right_index < right_size)
  {
    if (arr_left[left_index] < arr_right[right_index])
    {
      // add left element to our source array
      arr[source_index] = arr_left[left_index];
      ++left_index;
    }
    else 
    {
      // otherwise the right element must be the smallest, so we add it
      arr[source_index] = arr_right[right_index];
      ++right_index;
    }

    // element was added, so we also increase source_index
    ++source_index;
  }

  // we handle left-over elements, if there are, and add them as well
  /* left side has left-over 
  if (left_index <= middle_index)
  {
    arr[source_index] = arr_left[left_index];
  }

  // right side has left-over
  if (right_index <= upper_bound)
  {
    arr[source_index] = arr_right[right_index];
  }
  */

  // left side left-over
  while (left_index < left_size)
  {
    arr[source_index] = arr_left[left_index];
    ++left_index;
    ++source_index;
  }

  // right side left-over
  while (right_index < right_size)
  {
    arr[source_index] = arr_right[right_index];
    ++right_index;
    ++source_index;
  }
}

void mergeSort(int arr[], int lower_bound, int upper_bound)
{
  // safe guard: invalid bounds
  if (lower_bound > upper_bound)
    return;

  // safe guard: single element stage reached
  if (lower_bound == upper_bound)
    return;

  // calculate the middle element's index
  int middle_index = (upper_bound - lower_bound) / 2 + lower_bound;

  // call mergeSort on left subarray (including middle element)
  mergeSort(arr, lower_bound, middle_index);

  // call mergeSort on right subarray
  mergeSort(arr, middle_index + 1, upper_bound);

  // "merge" elements back together
  merge(arr, lower_bound, middle_index, upper_bound);
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
  mergeSort(arr, 0, arr_size - 1);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}