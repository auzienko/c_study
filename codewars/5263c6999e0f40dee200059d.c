/*
Alright, detective, one of our colleagues successfully observed our target person, Robby the robber. We followed him to a secret warehouse, where we assume to find all the stolen stuff. The door to this warehouse is secured by an electronic combination lock. Unfortunately our spy isn't sure about the PIN he saw, when Robby entered it.

The keypad has the following layout:

┌───┬───┬───┐
│ 1 │ 2 │ 3 │
├───┼───┼───┤
│ 4 │ 5 │ 6 │
├───┼───┼───┤
│ 7 │ 8 │ 9 │
└───┼───┼───┘
    │ 0 │
    └───┘
He noted the PIN 1357, but he also said, it is possible that each of the digits he saw could actually be another adjacent digit (horizontally or vertically, but not diagonally). E.g. instead of the 1 it could also be the 2 or 4. And instead of the 5 it could also be the 2, 4, 6 or 8.

He also mentioned, he knows this kind of locks. You can enter an unlimited amount of wrong PINs, they never finally lock the system or sound the alarm. That's why we can try out all possible (*) variations.

* possible in sense of: the observed PIN itself and all variations considering the adjacent digits

Can you help us to find all those variations? It would be nice to have a function, that returns an array (or a list in Java and C#) of all variations for an observed PIN with a length of 1 to 8 digits. We could name the function getPINs (get_pins in python, GetPINs in C#). But please note that all PINs, the observed one and also the results, must be strings, because of potentially leading '0's. We already prepared some test cases for you.

Detective, we are counting on you!

For C# user: Do not use Mono. Mono is too slower when run your code.
*/

#include <stdlib.h>

//Function should return an array of c-strings with all possible PINs.
//It must allocate all required meomry, but there are no requirements
//as to how it should be done. It must be possible to free
//allocated memory with a call to free_pins.
//Upon return, count should contain the amount of returned PINs.

int str_len(const char *str)
{
    int    result;

    result = 0;
    while (*(str++))
        result++;
    return (result);
}

const char** get_pins(const char* observed, size_t* count) 
{
    const char  *variants[] = {"08", "124", "1235", "236", 
    "1457", "24568", "3569", "478", "05789", "689"};
    const int   leng[] = {2, 3, 4, 3, 4, 5, 4, 3, 5, 3};
    int         *indices;
    int         i;
    int         j;
    int         size;
    char        **result;

    size = str_len(observed);
    i = -1;
    *count = 1;
    while (++i < size)
    {
        *count *= (leng[observed[i] - '0']);
    }
    result = NULL;
    result = (char **)malloc(sizeof(char *) * *count + 1);
    if (result == NULL)
        return (NULL);        
    result[*count] = NULL;
    indices = NULL;
    indices = (int *)malloc(sizeof(int) * size);
    if (indices == NULL)
        return (NULL);
    i = -1;
    while (++i < size)
        indices[i] = 0;
    i = -1;
    while (++i < (int)*count)
    {
        result[i] = (char *)malloc(sizeof(char *) * (size + 1));
        if (result[i] == NULL)
            return (NULL);
        result[i][size] = '\0';
    }
    j = 0;
    while(j < (int)*count)
    {
        i = -1;
        while (++i < size)
        {
            result[j][i] = variants[observed[i] - '0'][indices[i]];
        }
        while (i-- > 0)
        {
            if ((indices[i] + 1) < leng[observed[i] - '0'])
            {
                indices[i]++;
                break;
            }
            else
            {
               indices[i] = 0;
            }
        }
        j++;
    }
    free(indices);
    return (result);
}

//This function will be called once per every call to get_pins
//with a pointer value returned by such call.
void free_pins(const char ** pins) {
    //...do your cleanup, if necessary
    int i;

    i = -1;
    while (pins[++i])
    {
        free(pins[i]);
        pins[i] = NULL;
    }
    free(pins);
}

int main()
{
    const char      *observed = "234";
    const char      **result;
    size_t          count;

    count = 0;
    result = get_pins(observed, &count);
    free_pins(result);
    return (0);
}