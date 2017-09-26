#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define g 9.8 ///gravitational acceleration
#define b 3.5 ///channel width
#define nm 0.015 ///manning coefficient
#define Q 4 ///discharge
#define m 1.5
#define s 0.001
#define H0 1. ///water level at x=0
#define L 2000. ///channel length
#define Nx 2000 ///number of discrete point

double h[Nx+1];
double dx;

int main()
{
    dx=L/Nx;
    printf("hello world\n");

    return 0;
}
