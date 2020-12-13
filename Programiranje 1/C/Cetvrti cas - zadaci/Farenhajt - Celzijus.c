#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
float x;
printf("Vasa temperatura u Farenhajtima je: ");
scanf("%f", &x);
printf("%.2f = %.2f\n", x, (x-32)*5/9);
return 0;
}
