#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 64
int get_unit(int num, char **unit)
{
	(*unit) = (num == 0) ? "year" :
						(num == 1) ? "day"	:
						(num == 2) ? "hour" :
						(num == 3) ? "minute" : "second";

	return 0;
}

#define TIME_ARR_SIZE 5
int concat_str(int arr[TIME_ARR_SIZE], char **result)
{
	int i, last = 0, mid = 0, elem_cnt;
	char buff[BUF_SIZE];
	char *unit;

	for (i = TIME_ARR_SIZE-1; i > 0; i--) {
		if (arr[i] > 0) {
			if (!last) {
				last = i;
			}

			elem_cnt++;
		}
	}

	for (i = last-1; i > 0; i--) {
		if (arr[i] > 0) {
			mid = i;
			break;
		}
	}

	for (i = 0; i < TIME_ARR_SIZE; i++) {
		memset(buff, 0x0, BUF_SIZE);

		if (arr[i] > 0) {
			get_unit(i, &unit);
			if (arr[i] == 1) {
				snprintf(buff, BUF_SIZE-1, "%d %s", arr[i], unit);
			} else {
				snprintf(buff, BUF_SIZE-1, "%d %ss", arr[i], unit);
			}

			fprintf(stderr, "i : %d %d %d %d\n", i, arr[i], arr[i+1], arr[i+2]);

			if (elem_cnt > 1) {
				if (i == mid) {
					strcat(buff, " and ");
				} else if (i != last) {
					strcat(buff, ", ");
				}
			}
		}

		strcat((*result), buff);
	}

	return 0;
}

#define RES_SIZE 1024
char *formatDuration(int seconds)
{
	int time_arr[TIME_ARR_SIZE] = {0, };
	int years, days, hours, minutes;
	char *result;

	result = (char *)malloc(sizeof(char) * RES_SIZE);

	if (seconds == 0) {
		snprintf(result, BUF_SIZE-1, "now");
		goto done;
	}

	years = seconds / (365 * 24 * 60 * 60);
	seconds -= years * 365 * 24 * 60 * 60;

	days = seconds / (24 * 60 * 60);
	seconds -= days * 24 * 60 * 60;

	hours = seconds / (60 * 60);
	seconds -= hours * 60 * 60;

	minutes = seconds / 60;
	seconds -= minutes * 60;

	time_arr[0] = years;
	time_arr[1] = days;
	time_arr[2] = hours;
	time_arr[3] = minutes;
	time_arr[4] = seconds;

	concat_str(time_arr, &result);

done:
	return result;
}

int main(void)
{
	char *result;

	result = formatDuration(2520059);
	printf("%s\n", result);

	free(result);

	return 0;
}
