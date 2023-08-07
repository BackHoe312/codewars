#include <stdio.h>
#include <stdlib.h>

int *snail(size_t *outsz, const int **mx, size_t rows, size_t cols) 
{
	int *res = NULL;
	int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
	int i;
	int index = 0;

	(*outsz) = rows * cols;
	res = (int *)malloc(sizeof(int) * (*outsz));
	if (!res) {
		fprintf(stderr, "malloc failed\n");
		goto err;
	}

	while (index < (*outsz)) {
		for (i = left; i <= right; i++) {
			res[index++] = mx[top][i];
		}
		top++;

		for (i = top; i <= bottom; i++) {
			res[index++] = mx[i][right];
		}
		right--;

		if (top <= bottom) {
			for (i = right; i >= left; i--) {
				res[index++] = mx[bottom][i];
			}
			bottom --;
		}

		if (left <= right) {
			for (i = bottom; i >= top; i--) {
				res[index++] = mx[i][left];
			}
			left++;
		}
	}

	return res;
err:
	return NULL;
}
