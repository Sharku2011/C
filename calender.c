#include <stdio.h>
#include <stdlib.h>

int cal(void)
{
	int year, month, date, checkweek, checkcal, week, cal, i, j, check;
	int monthday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int summonth = 0;

	printf("'�� �� ��' �� �Է��� �ּ��� : ");
	check = scanf("%d %d %d",&year, &month, &date);

	if (check != 3 || month < 0 || month > 12 || date < 1 || date > monthday[month])	//�Է��� �߸� �� ��� �޼����� ����ϰ� �����ŵ�ϴ�.
	{
		printf("�Է��� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���.\n");
		exit(0);
	}

	if (year < 2000)
	{
		printf("������ 2000�� �̻��� ������ �Է��Ͽ� �ּ���.\n");
		exit(1);
	}

	for (i = 0; i < month; i++)
	{
		summonth = summonth + monthday[i];
	}

	cal = 365 * (year - 2000) + (year - 1996)/4 - (year - 2000)/100 + (year - 2000)/400 + summonth;					//2000�� 1�� 1�Ϸκ��� �Է��� ���� 1�ϱ����� ��¥�� ����մϴ�.
	week = cal + date - 1;		//2000�� 1�� 1�Ϸκ��� �Է��� �������� ��¥������ ����մϴ�.

	checkweek = week % 7;		//�Է��� ���� ������ üũ
	checkcal = cal % 7;			//�Է��� ���� 1���� ������ üũ

	printf("			%d��\n",month);			//�޷� ��ºκ� ����
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
	if (month == 2)			//������ ��� ���� ���� 28�Ͽ��� 29�Ϸ� �ø��ϴ�.
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
	for (j = 1; j <= monthday[month]; j++)		//�޷³��ڸ� ����ϴ� �κ��Դϴ�.
	{
		printf("%d	",j);
		if ((checkcal + j - 1) % 7 == 0)
		{
			printf("\n");
		}
	}
	printf("\n\n�Է��Ͻ� ��¥ %d�� %d�� %d�� �� ", year, month, date);

	switch (checkweek)
	{
		case 0:
		{
			printf("��");
			break;
		}
		case 1:
		{
			printf("��");
			break;
		}
		case 2:
		{
			printf("��");
			break;
		}
		case 3:
		{
			printf("ȭ");
			break;
		}
		case 4:
		{
			printf("��");
			break;
		}
		case 5:
		{
			printf("��");
			break;
		}
		case 6:
		{
			printf("��");
			break;
		}
	}
	printf("���� �Դϴ�.\n");
}
