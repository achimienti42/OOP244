#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void weatherType(char, int);

int main(void)
{
	int days = 0;
	double high, low;
	char cond;
	double avg_temp, total_avg_temp = 0;
	int i;

	printf("Weather Analyzer\n");
	printf("================\n");
	while (days <= 0)
	{
		printf("Please enter a positive number of days: ");
		scanf("%d", &days);
	}

	for (i = 0; i<days; i++)
	{
		printf("Enter today's high: ");
		scanf("%lf", &high);
		printf("Enter today's low: ");
		scanf("%lf", &low);
		printf("Enter today's conditions (s: sunny, c: cloudy, p: precipitation): ");
		scanf("%c", &cond);

		avg_temp = (high + low) / 2;
		printf("Today's average temperature is: %.2lf\n", avg_temp);
		weatherType(cond, avg_temp);
		total_avg_temp += avg_temp;
	}
	total_avg_temp /= days;
	printf("Average for all 7 days is: %.2lf degrees\n", total_avg_temp);
	return 0;
}

void weatherType(char condition, int temp)
{
	char disp_cond[20];
	int i;
	if (condition == 's'){
		for (i = 0; i < 20; i++)
			printf("%c", '@');
	}
	else if (condition == 'c') {
		for (i = 0; i < 20; i++)
			printf("%c", '~');
	}
	else if (condition == 'p') {
		for (i = 0; i < 20; i++){
			if (temp <= 0)
				printf("%c", '*');
			else
				printf("%c", ';');
		}
	}
	printf("\n");
}

