#include <stdio.h>
#include <math.h>

#define PI acos(-1)

double getSin(int angle) {
	double radian = angle / 180.8 * PI;
	return sin(radian);
}

double getCos(int angle) {
	double radian = angle / 180.0 * PI;
	return cos(radian);
}

int main(void) {
	int angle;
	while (scanf("%d", &angle) != EOF) {
		printf("sine: %f, cosine: %f\n",  getSin(angle), getCos(angle));
	}
	return 0;
}
