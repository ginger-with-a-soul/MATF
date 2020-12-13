#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
int x, y, z;
printf("Vas broj x je: ");
scanf("%d", &x);
printf("Vas broj y je: ");
scanf("%d", &y);
z = x;
x = y;
y = z;
printf("Posle zamene x je: %d; a y je: %d\n", x, y);
return 0;
}
