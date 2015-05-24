#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char* randnum(unsigned int length);
void marking(char* str1, char* str2, unsigned int* grade);
int IsOverlap(char* str);

void main(void)
{
	unsigned int grade[2] = { 0 };
	char* ans;
	unsigned int length, idx,check;
	printf("���� ���̽��� ����\n");
	printf("������ ������ �ڸ����� �����ּ��� (1~10) : ");
	scanf("%u", &length);
	char* user = (char*)calloc(length,sizeof(char));
	ans = randnum(length);
	while (1)
	{
		fflush(stdin);
		check = 0;
		grade[0] = 0;
		grade[1] = 0;
		printf("%u�ڸ��� �ڸ������� �ߺ����� �ʴ� ���ڸ� �Է��ϼ���.\n", length);
		gets(user);
		if (strlen(user) < length)
		{
			continue;
		}
		if (IsOverlap(user) == 1)
		{
			printf("�ߺ��Ǵ� ���ڴ� �Է��Ͻ� �� �����ϴ�.\n");
			continue;
		}
		for (idx = 0; idx < length; idx++)
		{
			if (isdigit(user[idx]) == 0)
			{
				printf("���ڸ� �Է��Ͻ� �� �ֽ��ϴ�.\n",user[idx]);
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			printf("%s\n", user);
			continue;
		}
		marking(ans, user, grade);
		printf("%s, %s, %uS %uB\n", ans, user, grade[0], grade[1]);
		if (grade[0] == length)
		{
			printf("�����մϴ�! �¸��ϼ̽��ϴ�.\n");
			break;
		}
	}
}

char* randnum(unsigned int length)
{
	char* ans = (char*)calloc((length + 1),sizeof(char));
	char add;
	unsigned int idx, idx2;
	if (length < 1)
	{
		printf("���ڿ��� ���̴� 0���� Ŀ���մϴ�.\n");
		exit(0);
	}
	else if (length > 10)
	{
		printf("���ڿ��� ���̴� 10���� Ŭ �� �����ϴ�.\n");
		exit(1);
	}
	else
	{
		srand((unsigned)time(0));
		for (idx = 0; strlen(ans) < length; idx++)
		{
			add = (rand() % 10) + 48;
			if (strlen(ans)>0)
			{
				idx2 = 0;
				while (idx2 <= strlen(ans))
				{
					if (add == ans[idx2])
					{
						add = (rand() % 10) + 48;
						idx2 = 0;
					}
					else
					{
						idx2++;
					}
				}
			}
			ans[idx] = add;
		}
		ans[(length + 1)] = '\0';
		return ans;
	}
}

int IsOverlap(char* str)
{
	unsigned int idx1, idx2, check;
	for (idx1 = 0; idx1 < strlen(str) + 1; idx1++)
	{
		check = 0;
		for (idx2 = 0; idx2 < strlen(str) + 1; idx2++)
		{
			if (str[idx1] == str[idx2])
			{
				check++;
				if (check > 1)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void marking(char* str1, char* str2, unsigned int* grade)
{
	unsigned int idx1, idx2;
	for (idx1 = 0; idx1 < strlen(str1); idx1++)
	{
		for (idx2 = 0; idx2 < strlen(str2); idx2++)
		{
			if (str1[idx1] == str2[idx2])
			{
				if (idx1 == idx2)
				{
					grade[0]++;
					break;
				}
				else
				{
					grade[1]++;
					break;
				}
			}
		}
	}
}
