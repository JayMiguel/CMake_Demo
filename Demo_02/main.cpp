#include <iostream>
#include "math/caculator.h"

int main(int argc, char** argv)
{
    int a = 6;
    int b = 3;

    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", reduce(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %d\n", substract(a, b));

    return 0;
}