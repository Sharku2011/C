/*사용자가 지정한 길이의 
'숫자로만 이루어진 난수 문자열'을 생성해서
사용자로부터 새로운 숫자로만 구성된 문자열을 입력받아
기존에 생성한 문자열과 비교하여
같은 숫자가 있고 위치도 동일하면 스트라이크,
같은 숫자가 있지만 문자열에서의 위치가 다를경우 볼로 인식해서
처음에 만든 난수 문자열을 정확히 맞추는 프로그램입니다.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void randnum(char* ans, unsigned int length);				//난수문자열 생성함수입니다.
void marking(char* str1, char* str2, unsigned int* grade);	//두개의 문자열을 받아서 비교한 뒤 점수를 매기는(스트라이크와 볼을 구분하는) 함수입니다.
int IsOverlap(char* str);									//문자열 안에 동일한 숫자가 2개 이상 존재하는지 파악하는 함수입니다. 0000 같은 입력을 방지하기 위한 함수입니다.

void main(void)
{
	unsigned int grade[2] = { 0 };				//grade[0]은 스트라이크, grade[1]은 볼에 해당합니다.
	char *user, *ans;							//user는 입력받는 문자열, ans는 처음에 생성하는 난수 문자열입니다.
	char name[11];
	unsigned int length, idx, check, trial;
	time_t start, end;							//랭킹 기록을 위한 타이머입니다.
	FILE *score;


	printf("##########숫자 베이스볼 게임##########\n");
	printf("게임을 진행할 자릿수를 정해주세요 (1~10) : ");
	scanf("%u", &length);

	user = (char*)calloc(length+1, sizeof(char));
	ans = (char*)calloc(length+1, sizeof(char));

	//난수문자열 생성.
	randnum(ans, length);
	start = time(0);

	//시도횟수입니다.
	trial = 0;
	
	while (1)
	{
		while (getchar() != '\n')
		check = 0;
		grade[0] = 0;
		grade[1] = 0;
		printf("\n%u자리의 자릿수끼리 중복되지 않는 숫자를 입력하세요.\n자릿수를 넘길 경우 넘어간 부분은 무시됩니다.\n\n", length);
		fgets(user,length+1,stdin);
		if (strlen(user) != length)
		{
			continue;
		}
		if (IsOverlap(user) == 1)
		{
			printf("중복되는 숫자는 입력하실 수 없습니다.\n");
			continue;
		}
		for (idx = 0; idx < length; idx++)
		{
			if (isdigit(user[idx]) == 0)
			{
				printf("숫자만 입력하실 수 있습니다.\n엔터 키를 누르시면 다시 입력하실 수 있습니다.", user[idx]);
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			continue;
		}
		marking(ans, user, grade);
		trial++;
		printf("%uS %uB\n", grade[0], grade[1]);
		if (grade[0] == length)
		{
			end = time(0);
			while (getchar() != '\n');
			printf("축하합니다! 승리하셨습니다. 도전횟수 : %u 회\n", trial);
			printf("이름을 입력해 주세요.(한글 5자, 영문 10자 이내) : ");
			fgets(name,11,stdin);
			score = fopen("score.txt", "a");
			fprintf(score, "%s도전자 : %s, 도전 길이 : %u, 시도 횟수 : %u, 소요 시간 : %d초\n", asctime(localtime(&end)), name, length, trial, end - start);
			fclose(score);
			break;
		}
	}
	//메모리 할당 해제
	free(ans);
	free(user);
}

void randnum(char* ans,unsigned int length)
{
	char add;
	unsigned int idx, idx2;
	if (length < 1)
	{
		printf("문자열의 길이는 0보다 커야합니다.\n");
		exit(0);
	}
	else if (length > 10)
	{
		printf("문자열의 길이는 10보다 클 수 없습니다.\n");
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