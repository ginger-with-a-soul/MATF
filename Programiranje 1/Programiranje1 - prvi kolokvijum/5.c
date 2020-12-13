#include <stdio.h>
#include <ctype.h>

int main(){

	char c1, c2, c3, c4;
	int k;
	
	scanf("%c%c%c%c %i", &c1, &c2, &c3, &c4, &k);

	if(!isupper(c1) || !isupper(c2) || !isupper(c3) || !isupper(c4) || k<0){
		printf("-1\n");
		return -1;
	}

	c1 = (c1 - 'A' + k) % 26;
	c1 = (c1 + 'A');
	c2 = (c2 - 'A' + k) % 26;
	c2 = (c2 + 'A');
	c3 = (c3 - 'A' + k) % 26;
	c3 = (c3 + 'A');
	c4 = (c4 - 'A' + k) % 26;
	c4 = (c4 + 'A');

	printf("%c%c%c%c\n", c1, c2, c3, c4);


return 0;
}
