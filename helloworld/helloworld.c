#include <stdio.h>

void swap(int *, int *);
int getSum();

int main(int argc, const char *argv[])
{
	int a = 5, b = 6;

	printf("%d\n", getSum());
	return 0;
}

int getSum() {
	int sum = 0;
	for (int i = 1; i <= 100; i++) {
		sum += i;
	}
	return sum;
}

void swap(int *x, int *y) {
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}
