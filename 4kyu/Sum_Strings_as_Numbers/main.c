#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strsum(const char *a, const char *b)
{
	int max_length, length_a, length_b;
	int num_a, num_b, digit, carry = 0, i;
	char *ret = NULL;

	length_a = strlen(a);
	length_b = strlen(b);
	max_length = (length_a > length_b) ? length_a : length_b;

	ret = (char *)malloc(sizeof(char) * max_length + 2);
	ret[max_length+1] = '\0';

	for (i = 0; i < max_length; i++) {
		num_a = i < length_a ? a[length_a - i - 1] - '0' : 0;
		num_b = i < length_b ? b[length_b - i - 1] - '0' : 0;

		digit = num_a + num_b + carry;
		carry = (digit >= 10) ? 1 : 0;

		ret[max_length - i] = digit % 10 + '0';
	}

	ret[0] = carry + '0';

  while (ret[0] == '0' && ret[1]) {
    memmove(ret, ret+1, max_length+1);
  }

	return ret;
}

int main(void)
{
	char *result;

	result = strsum("99", "1");
	printf("%s\n", result);

	return 0;
}
