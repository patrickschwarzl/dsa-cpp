// BINARY SEARCH
// recursive implementation of binary search.
//
// RUNTIME
//    best-case: O(1) -> target is the middle element of our original vector.
//    average-case: O(log n) -> simplifies to log n.
//    worst-case: O(log n) -> element is the first element, the last element or not in the vector at all.
//

#include <iostream>
#include <vector>

// This version of binary search has a runtime of O(n), with n being the number of elements inside the vector.
// Reason for that is the way we slice the vector by copying half of the elements into a new vector.
// This was a brute force approach to achieve a working implementation of binary search, yet missing out on O(log n) runtime.
/* int binarySearch(const std::vector<int> &vec, int target)
{
  // safeguard in case vector is empty
  if (vec.empty())
    return -1;

  // safeguard in case target is not in vector
  if (vec.size() == 1 && vec.at(0) != target)
    return -1;

  int middle = vec.size() / 2;

  if (vec.at(middle) == target)
  {
    return middle;
  }
  
  std::vector<int> vec_sliced;

  if (vec.at(middle) > target)
  {
    // proceed with left side
    for (std::size_t i = 0; i < middle; i++)
    {
      vec_sliced.push_back(vec.at(i));
    }

    return binarySearch(vec_sliced, target);
  }
  else
  {
    // proceed with right side
    for (std::size_t i = middle + 1; i < vec.size(); i++)
    {
      vec_sliced.push_back(vec.at(i));
    }

    int result = binarySearch(vec_sliced, target);

    if (result == -1)
      return -1;

    // modify result so we output the correct index, calling the algorithm on the right-side of our vector will incorrectly shift our index
    // shift index to the right to compensate for splitting
    return middle + 1 + result;
  }

  // recursively call binarySearch on the new vector
  return binarySearch(vec_sliced, target);
} */

int binarySearch(const std::vector<int> &vec, int lower_bound, int upper_bound, int target)
{
  if (upper_bound >= lower_bound)
  {
    int middle = lower_bound + (upper_bound - lower_bound) / 2;

    if (vec.at(middle) == target)
      return middle;

    if (vec.at(middle) > target)
    {
      // look at left side
      return binarySearch(vec, lower_bound, middle - 1, target);
    }
    else
    {
      // look at right side
      return binarySearch(vec, middle + 1, upper_bound, target);
    }
  }

  return -1;
}

int main()
{
  const std::vector<int> vec = {1, 3, 4, 5, 7, 9, 11}; // sorted

  // int result = binarySearch(vec, 9);

  int result = binarySearch(vec, 0, vec.size() - 1, 9);

  std::cout << result << std::endl;

  return 0;
}
