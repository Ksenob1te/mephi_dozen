#include <stdio.h>
#include <limits.h>


void task(const int* n) {
	if (*n <= 0)
		return;
	int first_item = 0, second_item = 1;
	printf("%d ", 1);
	for (int i = 0; i < *n - 1; i++) {
		int temp = second_item;
		if (INT_MAX - first_item < second_item) {
			printf("Overfloating");
			return;
		}
		second_item += first_item;
		first_item = temp;
		printf("%d ", second_item);
	}
	if (first_item)
		printf("\n%d", second_item / first_item);
	else
		printf("\nOnly one result");

}



int main() {
	int n = 0;
	int x = scanf("%d", &n);
	// printf("%d", x);
	if (feof(stdin)) {
		return 0;
	}
	if (x <= 0) {
		printf("Incorrect input");
		return 0;
	}
	task(&n);
	//printf("%d", n);
	return 0;

}
