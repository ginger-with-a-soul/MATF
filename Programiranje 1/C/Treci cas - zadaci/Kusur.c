#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
int x, y, z;
printf("Unesite broj kupljenih artikala, cenu tog kupljenog artikla i kolicinu novca koji ste dali kasirki: ");
scanf("%d %d %d", &x, &y, &z);
printf("Vas kusur je: %d\n", z-(x*y));
return 0;
}
