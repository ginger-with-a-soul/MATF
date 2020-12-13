#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
unsigned x;
printf("Vas racun je: ");
scanf("%u", &x);
printf("%u=%u*5000", x, x/5000);
x = x-(x/5000*5000);
printf("+%u*2000", x/2000);
x = x-(x/2000*2000);
printf("+%u*1000", x/1000);
x = x-(x/1000*1000);
printf("+%u*500", x/500);
x = x-(x/500*500);
printf("+%u*200", x/200);
x = x-(x/200*200);
printf("+%u*100", x/100);
x = x-(x/100*100);
printf("+%u*50", x/50);
x = x-(x/50*50);
printf("+%u*20", x/20);
x = x-(x/20*20);
printf("+%u*10", x/10);
x = x-(x/10*10);
printf("+%u*1\n", x/1);
return 0;
}
