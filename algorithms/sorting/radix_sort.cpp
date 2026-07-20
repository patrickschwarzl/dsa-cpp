// RADIX SORT
// implementation of radix sort, using counting sort (stable) under the hood.
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

    for (int j = 0; j < arr_size; j++)
    {
      int num = (arr[j] / divider) % 10;

      // counting sort
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
  // int arr[] = {5, 2, 4, 9, -2, 13, 1, 3, 100, 232, 67, 50, 0, 3, -40, -10, 20};
  int arr[] = {343, 567, 819, 199, 201, 506, 784};
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  std::cout << "unsorted: ";
  printArray(arr, arr_size);

  radixSort(arr, arr_size);

  std::cout << "sorted: ";
  printArray(arr, arr_size);
}