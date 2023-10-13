#include <library.h>
#include <library2.h>


int main(void)
{
    int x;
    int y;

    // Ask for starting population size

    do
    {
        x = get_int("Start size: ");
    }
    while (x < 9);


    // Ask for ending population size

    do
    {
        y = get_int("End size: ");
    }
    while (y < x);


    // Calculate years

    int n = 0;
    while (x < y)
    {
        x = x + (x / 3) - (x / 4);
        n ++;
    }


    // Display Answer

    printf("Years: %i\n", n);
}
