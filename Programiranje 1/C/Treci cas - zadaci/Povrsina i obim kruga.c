#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {
double x;
printf("Poluprecnik kruga je: ");
scanf("%lf", &x);
printf("Obim Vaseg kruga je: %.2lf.\nPovrsina Vaseg kruga je: %.2lf\n", 2*x*M_PI, pow(x,2)*M_PI);
return 0;
}
