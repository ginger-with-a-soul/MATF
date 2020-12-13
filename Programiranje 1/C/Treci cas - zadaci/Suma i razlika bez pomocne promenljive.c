#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
int x, y;
printf("Uneti dva cela broja: ");
scanf("%d %d", &x, &y);
x = x+y;
y = x-2*y;
printf("Suma ova dva broja je: x=%d.\nRazlika ova dva broja je y=%d\n", x, y);
return 0;
}
