#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define g 9.8 ///gravitational acceleration
#define b 3.5 ///channel width
#define nm 0.015 ///manning coefficient
#define Q 4 ///discharge
#define alpha 1. ///energy correction error
#define m 1.5 ///side channel slope
#define s 0.001
#define h0 1. ///water level at x=0
#define L 100. ///channel length
#define Nx  100///number of discrete point
#define maxerr 1e-6 ///maximum error tolerance

double dx;
double h[Nx+1];
double x[Nx+1];
double error[Nx+1];

void init();
double R(double h);
double f(double h1, int i);
double bisection(int i);
void output(char *type);

int main()
{
    init();
    for(int i=1;i<Nx+1;i++){
        h[i]=bisection(i);
    }
    output("text");
    return 0;
}

void init()
{
    dx=L/Nx;
    for(int i=0;i<Nx+1;i++)
        x[i]=i*dx;
    h[0]=h0;
}

inline double R(double h)
{
    return (b*h+m*h*h)/(b+2*h*sqrt(1+m*m));
}

inline double f(double h1, int i)
{
    return (h0+(alpha*Q*Q)/(2*g*b*b*h0*h0)
            -h1-(alpha*Q*Q)/(2*g*b*b*h1*h1)
            -i*dx/2*((nm*nm*Q*Q/pow(R(h0),4/3)*b*b*h0*h0)
                     -(nm*nm*Q*Q/pow(R(h1),4/3)*b*b*h1*h1)
                     )
            );
}

double bisection(int i)
{
    double l,r,c;
    l=0;
    r=1;
    do{
        c=(l+r)/2;
        error[i]=abs(f(c,i));
        if(f(c,i)==0)
            return c;
        else if(f(c,i)*f(l,i)<0)
            r=c;
        else
            l=c;
    }while(error[i]>=maxerr);

    return c;
}

void output(char *type)
{
    printf("x_i\th_i\terr_i\n");
    for(int i=0;i<Nx+1;i++)
        printf("%f\t%f\t%f\n",x[i],h[i],error[i]);

    if(strcmp(type,"text")==0){
        FILE *data=fopen("../data.txt","w");
        FILE *err=fopen("../error.txt","w");
        for(int i=0;i<Nx+1;i++){
            fprintf(data,"%f %f\n",x[i],h[i]);
            fprintf(err,"%f\n",error[i]);
        }
        fclose(data); fclose(err);
    }
}
