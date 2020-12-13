#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
int x, y;
printf("Unesite celobrojnu vrednost za x: ");
scanf("%d", &x);
printf("Unesite celobrojnu vrednost za y: ");
scanf("%d", &y);
printf("%d+%d=%d\n", x, y, x+y);
printf("%d-%d=%d\n", x, y, x-y);
printf("%d*%d=%d\n", x, y, x*y);
printf("%d/%d=%d\n", x, y, x/y);
printf("%d mod %d=%d\n", x, y, x%y);
return 0;
}
