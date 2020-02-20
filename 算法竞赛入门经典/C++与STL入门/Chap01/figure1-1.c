#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int a, b, c ;
	scanf("%d%d%d", &a, &b, &c);
	printf("Average value is %.3f\n", (a + b + c) / 3.0);
	return 0;
}
