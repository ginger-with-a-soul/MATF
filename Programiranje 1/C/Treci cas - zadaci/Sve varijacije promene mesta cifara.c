#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
int x, h, s, d, j;
printf("Unesite cetvorocifren ceo broj: ");
scanf("%d", &x);
h = x/1000;
s = x/100%10;
d = x/10%10;
j = x%10;
printf("Proizvod svih cifara Vaseg broja je: %d\n", h*s*d*j);
printf("Razlika sume krajnjih i srednjih cifara je: %d\n", (h+j)-(s+d));
printf("Suma kvadrata cifara je: %.0f\n", pow((float)h,2)+pow((float)s,2)+pow((float)d,2)+pow((float)j,2));
printf("Broj u obrnutom poretku je: %d\n", j*1000+d*100+s*10+h);
printf("Zamenom mesta cifre stotine i jedinice dobijamo broj: %d\n", h*1000+j*100+d*10+s);
return 0;
}
