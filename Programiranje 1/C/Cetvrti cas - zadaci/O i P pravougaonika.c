#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
float x, y;
printf("Duzine stranica Vaseg pravougaonika su: ");
scanf("%f %f", &x, &y);
printf("Obim Vaseg pravougaonika je: %.2f.\nPovrsina Vaseg pravougaonika je: %.2f", 2*(x+y), x*y);
return 0;
}
