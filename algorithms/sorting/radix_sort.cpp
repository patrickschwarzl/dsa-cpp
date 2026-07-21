// RADIX SORT
// implementation of radix sort, using counting sort (stable) under the hood. No negative
// values allowed. Reused some helper functions and modified my counting sort algorithm.
//
// RUNTIME
//    best-case: O() -> 
//    average-case: O() -> 
//    worst-case: O() -> 

#include <iostream>
#include <string>

// small helper function to bypass the need of <cmath>, while also returning
// an integer instead of a double (when using std::pow())
int toPowerOf(int number, int power_of)
{
  if (power_of == 0)
    return 1;

  int output = number;

  for (int i = 1; i < power_of; i++)
  {
    output *= number;
  }

  return output;
}

// helper function to fill array with given integer
void fillArrayWith(int arr[], int arr_size, int fill)
{
  for (int i = 0; i < arr_size; i++)
  {
    arr[i] = fill;
  }
}

// this version of counting sort is very similar to the one I already wrote in counting_sort.cpp,
// yet is slightly modified to match the new requirements. It does not determine the smallest value
// and uses a range from 0 up to the largest digit instead.
void countingSort(int arr[], int arr_size, int divider)
{
  // find largest digit in array
  int largest_digit = 0;
  int num = 0;

  for (int i = 0; i < arr_size; i++)
  {
    num = (arr[i] / divider) % 10;

    if (num > largest_digit)
    {
      largest_digit = num;
    }
  }

  // create temporary array, initialized with 0s
  int temp_size = largest_digit + 1;
  int arr_temp[temp_size];

  // fill array with 0s
  fillArrayWith(arr_temp, temp_size, 0);

  // count number of occurrences
  for (int i = 0; i < arr_size; i++)
  {
    num = (arr[i] / divider) % 10;
    arr_temp[num]++;
  }

  // compute prefix sums
  for (int i = 1; i < temp_size; i++)
  {
    arr_temp[i] += arr_temp[i - 1];
  }

  // shift array one index to the right, emitting value on last index
  for (int i = largest_digit; i >= 1; i--)
  {
    arr_temp[i] = arr_temp[i - 1];
  }

  // reset value at index 0
  arr_temp[0] = 0;

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
    num = (arr_copy[i] / divider) % 10;
    int index = arr_temp[num];

    // add value in correct position
    arr[index] = arr_copy[i];

    // increase position
    arr_temp[num]++;
  }
}

void radixSort(int arr[], int arr_size)
{
  // nothing to sort
  if (arr_size <= 1)
    return;

  // find largest number to determine its number of digits
  int target = 0;

  for (int i = 0; i < arr_size; i++)
  {
    if (arr[i] > target)
    {
      target = arr[i];
    }
  }

  std::string target_str = std::to_string(target);

  // represents the amount of digits our largest integer has
  int max_digits = target_str.length();

  // run counting sort on each individual digit | starting from the least significant digit
  for (int digit = 0; digit < max_digits; digit++)
  {
    // get access to the individual digits 
    int divider = 1;
    divider = toPowerOf(10, digit);

    countingSort(arr, arr_size, divider);
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
  int arr[] = {343, 567, 819, 199, 201, 506, 784, 111, 12, 99, 3};
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  std::cout << "unsorted: ";
  printArray(arr, arr_size);

  radixSort(arr, arr_size);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}