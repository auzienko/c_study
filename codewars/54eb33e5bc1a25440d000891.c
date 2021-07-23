/*
My little sister came back home from school with the following task: given a squared sheet of paper she has to cut it in pieces which, when assembled, give squares the sides of which form an increasing sequence of numbers. At the beginning it was lot of fun but little by little we were tired of seeing the pile of torn paper. So we decided to write a program that could help us and protects trees.

Task
Given a positive integral number n, return a strictly increasing sequence (list/array/string depending on the language) of numbers, so that the sum of the squares is equal to n².

If there are multiple solutions (and there will be), return as far as possible the result with the largest possible values:

Examples
decompose(11) must return [1,2,4,10]. Note that there are actually two ways to decompose 11², 11² = 121 = 1 + 4 + 16 + 100 = 1² + 2² + 4² + 10² but don't return [2,6,9], since 9 is smaller than 10.

For decompose(50) don't return [1, 1, 4, 9, 49] but [1, 3, 5, 8, 49] since [1, 1, 4, 9, 49] doesn't form a strictly increasing sequence.

Note
Neither [n] nor [1,1,1,…,1] are valid solutions. If no valid solution exists, return nil, null, Nothing, None (depending on the language) or "[]" (C) ,{} (C++), [] (Swift, Go).

The function "decompose" will take a positive integer n and return the decomposition of N = n² as:

[x1 ... xk] or
"x1 ... xk" or
Just [x1 ... xk] or
Some [x1 ... xk] or
{x1 ... xk} or
"[x1,x2, ... ,xk]"
depending on the language (see "Sample tests")

Note for Bash
decompose 50 returns "1,3,5,8,49"
decompose 4  returns "Nothing"
Hint
Very often xk will be n-1.
*/

// the result will be free-d
#include <stdlib.h>

long long	pw(long long n)
{
	return (n * n);
}

long long	brut_sqr(long long n)
{
	long long result;

	if (n == 0 || n == 1)
		return(n);
	result = 1;
	while (pw(++result) <= n);
	if (pw(result) == n)
		return (result);
	else
		return ((result - 1));
}

char	*null_string()
{
	char	*result;

	result = (char *)malloc(sizeof(char) * 3);
	result[0] = '[';
	result[1] = ']';
	result[2] = '\0';
	return (result);
}

char 	*output_solution(long long *array, int size)
{
	char		*tmp_result;
	char		*result;
	int			i;
	int			j;
	int			k;
	long long	buf;

	if (size < 2)
		return (null_string());
	i = -1;
	j = size + 1; //, +[]
	while (++i < size)
	{
		buf = array[i];
		while (buf)
		{
			buf /= 10;
			j++;
		}		
	}
	tmp_result = NULL;
	result = NULL;
	tmp_result = (char *)malloc(sizeof(char) * j);
	result = (char *)malloc(sizeof(char) * j);
	if (tmp_result == NULL || result == NULL)
		return (null_string());
	tmp_result[j] = '\0';
	result[j] = '\0';
	tmp_result[j - 1] = '[';
	tmp_result[0] = ']';
	i = -1;
	k = 0;
	while (++i < size)
	{
		buf = array[i];
		while (buf)
		{
			tmp_result[++k] = buf % 10 + '0';
			buf /= 10;
		}
		if (i != size - 1)
			tmp_result[++k] = ',';
	}
	i = -1;
	k = j;
	while (++i <= j)
	{
		result[i] = tmp_result[--k];
	}
	free(tmp_result);
	return (result);
}

char* decompose(long long n) {
	// your code
	int			i;
	int			j;
	long long	tmp_ext[100] = {0};
	long long	tmp_rem[100] = {0};
	long long	tmp_e;
	long long	tmp_r;
	
	i = 0;
	j = 0;
	tmp_rem[0] = pw(n);
	tmp_ext[0] = n - 1;
	while (tmp_rem[i] > 0)
	{
		tmp_r = tmp_rem[i] - pw(tmp_ext[i]);
		tmp_e = brut_sqr(tmp_r);
		if (tmp_e < tmp_ext[i])
		{
			tmp_ext[i + 1] = tmp_e;
			tmp_rem[i + 1] = tmp_r;
			i++;
		}
		else
		{
			i -=1;
			tmp_ext[i] -= 1;
		}
	}
	return (output_solution(tmp_ext, i));
}

int main()
{
	char *result;

	result = decompose(76);
	free(result);
	return(0);
}