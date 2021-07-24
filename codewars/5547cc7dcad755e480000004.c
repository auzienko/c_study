/*
A friend of mine takes the sequence of all numbers from 1 to n (where n > 0).
Within that sequence, he chooses two numbers, a and b.
He says that the product of a and b should be equal to the sum of all numbers in the sequence, excluding a and b.
Given a number n, could you tell me the numbers he excluded from the sequence?
The function takes the parameter: n (n is always strictly greater than 0) and returns an array or a string (depending on the language) of the form:

[(a, b), ...] or [[a, b], ...] or {{a, b}, ...} or or [{a, b}, ...]
with all (a, b) which are the possible removed numbers in the sequence 1 to n.

[(a, b), ...] or [[a, b], ...] or {{a, b}, ...} or ... will be sorted in increasing order of the "a".

It happens that there are several possible (a, b). The function returns an empty array (or an empty string) if no possible numbers are found which will prove that my friend has not told the truth! (Go: in this case return nil).

Examples:
removNb(26) should return [(15, 21), (21, 15)]
or
removNb(26) should return { {15, 21}, {21, 15} }
or
removeNb(26) should return [[15, 21], [21, 15]]
or
removNb(26) should return [ {15, 21}, {21, 15} ]
or
removNb(26) should return "15 21, 21 15"
or

in C:
removNb(26) should return  {{15, 21}{21, 15}} tested by way of strings.
Function removNb should return a pointer to an allocated array of Pair pointers, each one also allocated. 
See examples of returns for each language in "RUN SAMPLE TESTS"
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Pair Pair;
struct Pair {
    long long first;
    long long snd;
};

long long get_sum(long long n)
{
    long long   result;

    result = (n + 1) * n / 2;
    return (result);
}

int    arr_append(Pair ***result, long long first, long long snd, int length)
{
    Pair    *buf;
    Pair    **tmp;
    int     i;

    buf = NULL;
    buf = (Pair *)malloc(sizeof(Pair));
    if (buf == NULL)
        return (EXIT_FAILURE);
    buf->first = first;
    buf->snd = snd;
    tmp = NULL;
    tmp = (Pair **)malloc(sizeof(Pair *) * length);
    if (tmp == NULL)
        return (EXIT_FAILURE);
    if (length > 1)
    {
        i = -1;
        while (++i < length - 1)
            *(tmp + i) = *(*result + i);
    }
    *(tmp + length - 1) = buf;
    if (*result != NULL)
        free(*result);
    *result = tmp;
    return(EXIT_SUCCESS);     
}

// fill length with the number of pairs in your array of pairs
Pair** removNb(long long n, int* length) {
  // your code
    long long   j;
    long long   sum;
    int         count;
    Pair        **result;

    count = 0;
    result = NULL;
    sum = get_sum(n);
    j = n / 2;
    /*
    i * j == sum - i - j
    i * j + i = sum - j
    i * (j + 1) = sum - j
    i = (sum - j)/(j + 1)
    */
    while (++j < n)
    {
        if ((sum - j) % (j + 1) == 0)
        {
            printf("first %lld snd %lld\n", j, (sum - j) / (j + 1));
            count++;
            arr_append(&result, j, (sum - j) / (j + 1), count);
        }
    }
    *length = count;
    return (result);
}

int main (void)
{
    int i;

    removNb(1000008, &i);
    return (EXIT_SUCCESS);
}