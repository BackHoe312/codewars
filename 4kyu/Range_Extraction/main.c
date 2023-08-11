#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *range_extraction(const int *args, size_t n)
{
	char *result;
	int start, end, i;

	result = (char *)malloc(sizeof(char) * n * 4);
	if (!result) {
		fprintf(stderr, "failed malloc\n");
		return NULL;
	}
	result[0] = '\0';
	
	i = 0;
	while (i < n) {
		start = args[i];
		end = args[i];

		while (i < n-1 && args[i+1] == args[i]+1) {
			i++;
			end = args[i];
		}

		if (start == end) {
			sprintf(result, "%s%d,", result, start);
		} else if (end - start == 1) {
			sprintf(result, "%s%d,%d,", result, start, end);
		} else {
			sprintf(result, "%s%d-%d,", result, start, end);
		}

		i++;
	}

	result[strlen(result)-1] = '\0';
	return result;
}

int main(void)
{
	char *result = NULL;
	int args[] = { -6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20 };


	result = range_extraction(args, 20ul);
	printf("%s\n", result);

	free(result);

	return 0;
}
