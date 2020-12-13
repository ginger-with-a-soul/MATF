#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {
double x1, x2, x3, y1, y2, y3, a, b,c, O, s, P;
printf("Koordinate temena A su: ");
scanf("%lf %lf", &x1, &y1);
printf("Koordinate temena B su: ");
scanf("%lf %lf", &x2, &y2);
printf("Koordinate temena C su: ");
scanf("%lf %lf", &x3, &y3);
a = sqrt(pow(x2-x3,2)+pow(y2-y3,2));
b = sqrt(pow(x3-x1,2)+pow(y3-y1,2));
c = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
O = a+b+c;
s = O/2;
P = sqrt(s*(s-a)*(s-b)*(s-c));
printf("Obim Vaseg trougla je: %.2lf\nPovrsina Vaseg trougla je: %.2lf\n", O, P);
return 0;
}
