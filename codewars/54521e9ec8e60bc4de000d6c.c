/*
The maximum sum subarray problem consists in finding the maximum sum of a contiguous subsequence in an array or list of integers:

maxSequence({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 9)
// should return 6, from sub-array: {4, -1, 2, 1}
Easy case is when the list is made up of only positive numbers and the maximum sum is the sum of the whole array. If the list is made up of only negative numbers, return 0 instead.

Empty list is considered to have zero greatest sum. Note that the empty list or array is also a valid sublist/subarray.
*/

#include <stddef.h>

int arraysum (const int* array, size_t n)
{
  int result;
  size_t  i;
  
  result = 0;
  i = 0;
  while (i < n)
  {
    result += array[i];
    i++;
  }
  return (result);
}


int maxSequence(const int* array, size_t n) {

    // <---- hajime!
  size_t i;
  size_t j;
  int result;
  int temp;
  
  result = 0;
  if (n != 0)
  {
    i = 0;
    j = 0;
    while (i < n - 1)
    {
      if (array[i] > 0)
      {
        j = i + 1;
        while (j <= n)
        {
          temp = arraysum(&array[i], j - i);
          if (temp > result)
          {
            result = temp;  
          }
          j++;
        }
      }
      i++;             
    }
  }    
  return (result);
}

int main ()
{
    int result;
     const int array[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    result = maxSequence(array, 9);
    return (0);
}