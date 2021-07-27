/*
Your task in order to complete this Kata is to write a function which formats a duration, given as a number of seconds, in a human-friendly way.

The function must accept a non-negative integer. If it is zero, it just returns "now". Otherwise, the duration is expressed as a combination of years, days, hours, minutes and seconds.

It is much easier to understand with an example:

formatDuration (62)    // returns "1 minute and 2 seconds"
formatDuration (3662)  // returns "1 hour, 1 minute and 2 seconds"
For the purpose of this Kata, a year is 365 days and a day is 24 hours.

Note that spaces are important.

Detailed rules
The resulting expression is made of components like 4 seconds, 1 year, etc. In general, a positive integer and one of the valid units of time, separated by a space. The unit of time is used in plural if the integer is greater than 1.

The components are separated by a comma and a space (", "). Except the last component, which is separated by " and ", just like it would be written in English.

A more significant units of time will occur before than a least significant one. Therefore, 1 second and 1 year is not correct, but 1 year and 1 second is.

Different components have different unit of times. So there is not repeated units like in 5 seconds and 1 second.

A component will not appear at all if its value happens to be zero. Hence, 1 minute and 0 seconds is not valid, but it should be just 1 minute.

A unit of time must be used "as much as possible". It means that the function should not return 61 seconds, but 1 minute and 1 second instead. Formally, the duration specified by of a component must not be greater than any valid more significant unit of time.
*/
#include <stdio.h>
#include <stdlib.h>

int str_len(char *str)
{
    char *tmp;

    tmp = str;
    while(*(str++));
    return(--str - tmp);
}

void    can_cat(char **dst, char *src)
{
    int     i;
    char    *tmp;

    i = str_len(*dst) + str_len(src);
    tmp = NULL;
    tmp = (char *)malloc(sizeof(char) * i + 1);
    if (tmp == NULL)
        return ;
    i = -1;
    while (*(*dst + ++i))
        tmp[i] = *(*dst + i);
    while (*(src))
    {
        tmp[i++] = *(src);
        src++;
    }
    tmp[i] = '\0';
    *dst = tmp;
    return ;    
}

char *int2str(int n)
{
    int     i;
    int     j;
    int     buf;
    char    *tmp_result;
    char    *result;

    buf = n;
    j = 0;
	while (buf)
	{
		buf /= 10;
		j++;
	}
	tmp_result = NULL;
	tmp_result = (char *)malloc(sizeof(char) * j + 1);
	if (tmp_result == NULL)
		return (NULL);
	tmp_result[j] = '\0';
    buf = n;
    i = -1;
	while (buf)
	{
		tmp_result[++i] = buf % 10 + '0';
		buf /= 10;
	}
    result = NULL;
    result = (char *)malloc(sizeof(char) * j + 1);
	if (result == NULL)
		return (NULL);
    result[j] = '\0';
    i = -1;
	while (++i < j)
	{
		result[i] = tmp_result[j - i - 1];
	}
	free(tmp_result);
    return (result);
}

char *formatDuration (int n) {
    long    div[] = {31536000, 86400, 3600, 60};
    int     temp[5] = {0};
    int     i;
    int     sz;
    char    *size_s[] = {" year", " day", " hour", " minute", " second"};
    char    *size_m[] = {" years", " days", " hours", " minutes", " seconds"};
    char    *result;

    result = NULL;
    result = (char*)malloc(sizeof(char));
    if (result == NULL)
        return (NULL);
    result[0] = '\0';
    if (n == 0)
    {
        can_cat(&result,"now");
        return (result);
    }
    i = -1;
    sz = 0;
    while (++i < 4)
    {
        temp[i] = n / div[i];
        if (temp[i] > 0)
            sz++;
        n %= div[i];
    }
    temp[i] = n;
     if (temp[i] > 0)
            sz++;
    i = -1;
    while (++i < 5)
    {
        if (temp[i] > 0)
        {
            if (temp[i] == 1)
            {
                can_cat(&result,"1");
                can_cat(&result, size_s[i]);
            }
            else
            {
                can_cat(&result,int2str(temp[i]));
                can_cat(&result, size_m[i]);
            }
            sz--;
            if (sz > 0)
            {
                if (sz == 1)
                    can_cat(&result," and ");
                else
                    can_cat(&result,", ");
            }              
        }
    }
    return (result);
}

int main(void)
{
    char    *result;

    can_cat(&result, "hello");
    printf("result is %s\n", formatDuration(0));
    printf("result is %s\n", formatDuration(1));
    printf("result is %s\n", formatDuration(3600));
    printf("result is %s\n", formatDuration(120));
    printf("result is %s\n", formatDuration(62));
    printf("result is %s\n", formatDuration(3662));    
    return (EXIT_SUCCESS);
}