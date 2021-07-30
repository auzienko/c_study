/*
From wikipedia https://en.wikipedia.org/wiki/Partition_(number_theory)

In number theory and combinatorics, a partition of a positive integer n, also called an integer partition, is a way of writing n as a sum of positive integers. Two sums that differ only in the order of their summands are considered the same partition.

For example, 4 can be partitioned in five distinct ways:

4, 3 + 1, 2 + 2, 2 + 1 + 1, 1 + 1 + 1 + 1.

We can write:

enum(4) -> [[4],[3,1],[2,2],[2,1,1],[1,1,1,1]] and

enum(5) -> [[5],[4,1],[3,2],[3,1,1],[2,2,1],[2,1,1,1],[1,1,1,1,1]].

The number of parts in a partition grows very fast. For n = 50 number of parts is 204226, for 80 it is 15,796,476 It would be too long to tests answers with arrays of such size. So our task is the following:

1 - n being given (n integer, 1 <= n <= 50) calculate enum(n) ie the partition of n. We will obtain something like that:
enum(n) -> [[n],[n-1,1],[n-2,2],...,[1,1,...,1]] (order of array and sub-arrays doesn't matter). This part is not tested.

2 - For each sub-array of enum(n) calculate its product. If n = 5 we'll obtain after removing duplicates and sorting:

prod(5) -> [1,2,3,4,5,6]

prod(8) -> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 18]

If n = 40 prod(n) has a length of 2699 hence the tests will not verify such arrays. Instead our task number 3 is:

3 - return the range, the average and the median of prod(n) in the following form (example for n = 5):

"Range: 5 Average: 3.50 Median: 3.50"

Range is an integer, Average and Median are float numbers rounded to two decimal places (".2f" in some languages).

Notes:
Range : difference between the highest and lowest values.

Mean or Average : To calculate mean, add together all of the numbers in a set and then divide the sum by the total count of numbers.

Median : The median is the number separating the higher half of a data sample from the lower half. (https://en.wikipedia.org/wiki/Median)

Hints:
Try to optimize your program to avoid timing out.

Memoization can be helpful but it is not mandatory for being successful.
*/
#include <stdlib.h>
#include <stdio.h>

void    tryadd(int **arr, int val, int *size)
{
    int     i;
    int     tmp;
    int     buf;
    int    *tmp_arr;

    if (*arr == NULL)
    {
        if ((*arr = (int *)malloc(sizeof(int))) == NULL)
            return ;
        *arr[0] = val;
        *size += 1;
        return ;
    }
    i = -1;
    tmp = val;
    while (++i < *size)
    {
        if ((*(*arr +i)) == val)
            return ;
        if ((*(*arr +i)) > tmp)
        {
            buf = *(*arr +i);
            *(*arr +i) = tmp;
            tmp = buf;
        }
    }
    *size += 1;
    if ((tmp_arr = (int *)calloc(*size, sizeof(int))) == NULL)
        return ;
    i = -1;
    while (++i < *size)
    {
        *(tmp_arr + i) = *(*arr + i);
    }
    *(tmp_arr + *size - 1) = tmp;
    free(*arr);
    *arr = tmp_arr;
}

char* part(int n) {
  // your code
    int     i;
    int     j;
    int     tmp;
    int     size;
    int     rage;
    int     *arr;
    int     *iarr;
    float   med;
    char    *result;


    iarr = NULL;
    size = 0;
    if (n > 1)
    {
        arr = (int *)calloc(n, sizeof(int));
        arr[0] = n - 1;
        arr[1] = 1;
        i = 1;
        tmp = 0;
    }
    while (n > 1)
    {
        if (arr[0] == 1)
            break;
        if (arr[i] != 1)
        {
            arr[i]--;
            tmp++;
        }
        else
        {
            arr[i] = 0;
            i--;
            tmp++;
            continue ;
        }
        arr[i + 1] = tmp;
        j = -1;
        tmp = 1;
        while (++j < n)
        {
            if (arr[j] == 0)
                break ;
            tmp *= arr[j];
        }
        if (tmp > n)
            tryadd(&iarr, tmp, &size);
        tmp = 0;
        i++;
    }
    size = n + size;
    arr = (int *)calloc(size, sizeof(int));
    i = -1;
    while (++i < n)
        arr[i] = i + 1;
    i--;
    while (++i < size)
        arr[i] = *(iarr + i - n);
    i = -1;
    if (size == 0)
        rage = n - 1;
    else
        rage = arr[size - 1] - 1;
    tmp = 0;
    i = -1;
    while (++i < size)
        tmp += arr[i];
    if ((size % 2) > 0)
        med = (n == 1) ? 1.0: arr[size / 2] * 1.0;
    else
        med = (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
    if ((result = (char *)malloc(sizeof(char) * 128)) == NULL)
        return (NULL);
    sprintf(result,"Range: %d Average: %.2f Median: %.2f", rage, (float)tmp /(size) ,med);
    free (iarr);
    return (result);
}

int main(void)
{
    char    *result;
 //   int     j;

//    j = powab(2,4);
    result = part(27);
    printf("%s\n", result);
    return (0);
}