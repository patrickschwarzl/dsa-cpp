// LINEAR SEARCH
// very trivial implementation on a raw array.
//
// RUNTIME
//    best-case: O(1) -> target is the first element in the array.
//    average-case: O(n) -> element is somewhere in the middle O(~n/2).
//    worst-case: O(n) -> having to iterate over the whole array, target is at the very end or not in the array.
//

#include <iostream>
#include <vector>

/* int linearSearch(const std::vector<int> &vec, int target)
{
  for (std::size_t i = 0; i < vec.size(); i++)
  {
    if (vec.at(i) == target)
      return i;
  }
  
  return -1;
} */

int linearSearch(const int arr[], std::size_t arr_size, int target)
{
  for (std::size_t i = 0; i < arr_size; i++)
  {
    if (arr[i] == target)
      return i;
  }

  return -1;
}

int main()
{
  // std::vector<int> vec = {1, 5, 7, 2, 9};
  // int result = linearSearch(vec, -2);

  const int arr[] = {1, 5, 7, 2, 9};
  std::size_t arr_size = sizeof(arr) / sizeof(arr[0]);

  int result = linearSearch(arr, arr_size, 5);

  std::cout << result << std::endl;

  return 0;
}
