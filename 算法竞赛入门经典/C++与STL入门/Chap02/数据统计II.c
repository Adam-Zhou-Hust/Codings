#include <stdio.h>

#define INF 100000000

int main(int argc, char *argv[]) {
	int min = INF, max = -INF;
	int sum = 0;
	int n, var, group = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &var);
			if (var < min) 
				min = var;
			if (var > max)
				max = var;
			sum += var;
		}
		if (group)
			printf("\n");
		printf("case %d: %d %d %.3f\n", ++group, min, max, (double)sum / n);
		min = INF, max = -INF, sum = 0;
	}
	return 0;
}
