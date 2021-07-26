/*
The rgb function is incomplete. Complete it so that passing in RGB decimal values will result in a hexadecimal representation being returned. Valid decimal values for RGB are 0 - 255. Any values that fall out of that range must be rounded to the closest valid value.

Note: Your answer should always be 6 characters long, the shorthand with 3 will not work here.

The following are examples of expected output values:

char output[7] = {0};

rgb(255, 255, 255, output); 
output == "FFFFFF";

rgb(255, 255, 300, output); 
output == "FFFFFF";

rgb(0, 0, 0, output); 
output == "000000";

rgb(148, 0, 211, output);
output == "9400D3";
*/
#include <stdlib.h>

int rgb(int r, int g, int b, char *output)
{   
   //pass the result to the 'char *output'
    int     tmp[3];
    int     buf;
    int     i;

    tmp[0] = (r <= 0) ? 0: (r > 255) ? 255 : r;
    tmp[1] = (g <= 0) ? 0: (g > 255) ? 255 : g;
    tmp[2] = (b <= 0) ? 0: (b > 255) ? 255 : b;
    i = -1;
    while (++i < 3)
    {
        buf = tmp[i] / 16;
        *(output + 2 * i) = (buf < 10) ? buf + '0' : buf - 10 + 'A';
        buf = tmp[i] % 16;
        *(output + 2 * i + 1) = (buf < 10) ? buf + '0' : buf - 10 + 'A';
    }
    *(output + 6) = '\0';
    return 0; 
}

int main(void)
{
    char result[6];

    rgb(255, 254, 275, &result);
    return(EXIT_SUCCESS);
}