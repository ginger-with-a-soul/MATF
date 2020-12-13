#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
float x, y, z, c;
printf("Duzina, sirina i visina sobe je: ");
scanf("%f %f %f", &x, &y, &z);
printf("Cena krecenja jednog m2 je: ");
scanf("%f", &c);
printf("Povrsina koju treba okreciti je: %.2f m2\nCena krecenja cele sobe je: %.2f\n", (x*y+2*x*z+2*y*z)*0.8, (x*y+2*x*z+2*y*z)*0.8*c);

return 0;
}
