/*
An Arithmetic Progression is defined as one in which there is a constant 
difference between the consecutive terms of a given series of numbers. 
You are provided with consecutive elements of an Arithmetic Progression. 
There is however one hitch: exactly one term from the original series is 
missing from the set of numbers which have been given to you. 
The rest of the given series is the same as the original AP. Find the missing term.

You have to write a function that receives a list, list size will always 
be at least 3 numbers. The missing term will never be the first or last one.

find_missing((const int[]){1,3,5,9,11}, 5)  => 7
*/

#include <stddef.h>

int find_missing(const int *nums, size_t n)
{
    int step;
  
    step = (nums[n - 1] - nums[0]) / (int)n;
    if (step)
    {
        while (--n > 0)
        {
            if ((nums[n] - nums[n - 1]) != step)
                return (nums[n - 1] + step);
        }
    }
    return nums[0];
}


int main()
{
    int result;
    result = find_missing((const int[]){-1, 1, 3, 5, 9}, 5ul);
    return (0);
}