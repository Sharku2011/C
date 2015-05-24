#include <stdio.h>
#include <stdlib.h>

int cal(void)
{
	int year, month, date, checkweek, checkcal, week, cal, i, j, check;
	int monthday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int summonth = 0;

	printf("'연 월 일' 을 입력해 주세요 : ");
	check = scanf("%d %d %d",&year, &month, &date);

	if (check != 3 || month < 0 || month > 12 || date < 1 || date > monthday[month])	//입력이 잘못 된 경우 메세지를 출력하고 종료시킵니다.
	{
		printf("입력이 잘못되었습니다. 다시 입력해주세요.\n");
		exit(0);
	}

	if (year < 2000)
	{
		printf("연도는 2000년 이상의 연도를 입력하여 주세요.\n");
		exit(1);
	}

	for (i = 0; i < month; i++)
	{
		summonth = summonth + monthday[i];
	}

	cal = 365 * (year - 2000) + (year - 1996)/4 - (year - 2000)/100 + (year - 2000)/400 + summonth;					//2000년 1월 1일로부터 입력한 달의 1일까지의 날짜를 계산합니다.
	week = cal + date - 1;		//2000년 1월 1일로부터 입력한 날까지의 날짜인지를 계산합니다.

	checkweek = week % 7;		//입력한 날의 요일을 체크
	checkcal = cal % 7;			//입력한 달의 1일의 요일을 체크

	printf("			%d月\n",month);			//달력 출력부분 시작
	printf("sun	mon	tue	wed	thu	fri	sat\n");
	if (checkcal == 0)
	{
		for (i = 1; i < 7; i++)
		{
			printf("	");
		}
	}
	else
	{
		for (i = 1; i < checkcal; i++)
		{
			printf("	");
		}
	}
	if (month == 2)			//윤달인 경우 달의 끝을 28일에서 29일로 늘립니다.
	{
		if (year%400 == 0)
		{
			monthday[month]++;
		}
		else if ((year%100)%4 == 0 && year%100 != 0)
		{
			monthday[month]++;
		}
	}
	for (j = 1; j <= monthday[month]; j++)		//달력날자를 출력하는 부분입니다.
	{
		printf("%d	",j);
		if ((checkcal + j - 1) % 7 == 0)
		{
			printf("\n");
		}
	}
	printf("\n\n입력하신 날짜 %d년 %d월 %d일 은 ", year, month, date);

	switch (checkweek)
	{
		case 0:
		{
			printf("토");
			break;
		}
		case 1:
		{
			printf("일");
			break;
		}
		case 2:
		{
			printf("월");
			break;
		}
		case 3:
		{
			printf("화");
			break;
		}
		case 4:
		{
			printf("수");
			break;
		}
		case 5:
		{
			printf("목");
			break;
		}
		case 6:
		{
			printf("금");
			break;
		}
	}
	printf("요일 입니다.\n");
}
