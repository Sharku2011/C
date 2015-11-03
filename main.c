/*사용자가 지정한 길이의 
'숫자로만 이루어진 난수 문자열'을 생성해서
사용자로부터 새로운 숫자로만 구성된 문자열을 입력받아
기존에 생성한 문자열과 비교하여
같은 숫자가 있고 위치도 동일하면 스트라이크,
같은 숫자가 있지만 문자열에서의 위치가 다를경우 볼로 인식해서
처음에 만든 난수 문자열을 정확히 맞추는 프로그램입니다.*/

#include "C:\numbb.h"

void numbb();

int main(void)
{
	numbb();
}

void numbb(void)
{
	unsigned int grade[2] = { 0 };				//grade[0]은 스트라이크, grade[1]은 볼에 해당합니다.
	char *user, *ans;							//user는 입력받는 문자열(답안), ans는 처음에 생성하는 난수 문자열입니다.
	char name[11];
	unsigned int length, idx, check, trial, timerOn;
	clock_t start, end;						//랭킹 기록을 위한 타이머입니다.
	FILE *rank;								//랭킹을 기록할 파일포인터입니다.

	SCORE newData;							//새로운 기록을 저장할 구조체입니다.
	List listDB;								//기존 기록을 저장해둘 링크드리스트입니다.
	SCORE* tmpArr;							//기존 기록을 읽어오는데 쓸 버퍼입니다.

	rank = fopen("NumbbRanking.txt", "ab");		//랭킹을 기록할 파일을 미리 생성해둡니다. 이미 존재한다면 아무 동작도 하지 않습니다.
	fclose(rank);
	createList(&listDB);						//링크드리스트를 초기화합니다.

	printf("##########숫자 베이스볼 게임##########\n");
	printf("게임을 진행할 자릿수를 정해주세요 (1~10) : ");
	//난이도를 결정하기 위해 입력을 받습니다.
	scanf("%u", &length);

	//사용자의 답안과 정답을 위한 문자열 공간을 할당합니다.
	user = (char*)calloc(length + 1, sizeof(char));
	ans = (char*)calloc(length + 1, sizeof(char));

	//난수문자열 생성.
	randnum(ans, length);

	//시도횟수를 초기화합니다.
	trial = 0;
	//타이머가 켜졌는지를 확인하기 위한 변수를 초기화합니다.
	timerOn = 0;
	
	while (1)
	{
		BUFFLUSH();
		check = 0;
		//채점 초기화(노 스트라이크 노 볼)
		grade[0] = 0;
		grade[1] = 0;
		printf("\n%u자리의 자릿수끼리 중복되지 않는 숫자를 입력하세요.\n자릿수를 넘길 경우 넘어간 부분은 무시됩니다.\n\n", length);
		//답안을 입력받습니다.
		getstr(user, length + 1);
		//입력받은 답안이 정해진 길이와 맞지 않을경우 다시 답안을 입력받도록 합니다.
		if (strlen(user) != length)
		{
			continue;
		}
		//입력받은 답안에 중복되는 숫자가 존재할 경우(1123,0048 등) 다시 답안을 입력받도록 합니다.
		if (IsOverlap(user) == 1)
		{
			printf("중복되는 숫자는 입력하실 수 없습니다.\n");
			continue;
		}
		//입력받은 답안에 숫자가 아닌것이 존재할 경우(a102, 0cs0 등) 다시 답안을 입력받도록 합니다.
		for (idx = 0; idx < length; idx++)
		{
			if (isdigit(user[idx]) == 0)
			{
				printf("숫자만 입력하실 수 있습니다.\n");
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			continue;
		}
		//올바른 입력이 들어왔을 경우 답안 채점함수 호출. 최초 입력시에는 타이머를 가동합니다.
		if (timerOn == 0)
		{
			start = clock(0);
			timerOn = 1;
		}
		marking(ans, user, grade);
		//시도횟수를 늘립니다.
		trial++;
		//채점 결과를 출력합니다.
		printf("%uS %uB\n", grade[0], grade[1]);
		//모든 숫자를 맞췄을 경우, 축하 메세지와 함께 기록을 파일에 저장합니다.
		if (grade[0] == length)
		{
			end = clock(0);
			printf("축하합니다! 승리하셨습니다. 도전횟수 : %u 회\n", trial);
			printf("이름을 입력해 주세요.(한글 5자, 영문 10자 이내) : ");
			getstr(name, 11);
			//사용자의 점수 정보를 담은 구조체를 생성합니다.
			setScore(&newData, name, length, trial, (end - start));
			
			//랭킹을 저장할 파일을 엽니다.
			rank = fopen("NumbbRanking.txt", "r+b");
			//선언해둔 링크드리스트에 기존 기록을 저장합니다. 기존 기록이 없다면 버퍼에 0을 반환합니다.
			tmpArr = freadList(rank, &listDB);
			//링크드리스트에 새 기록을 추가합니다.
			addNode(&listDB, &newData);
			//추가된 기록을 콘솔 화면에 출력하고 파일에 기록합니다.
			printRank(&listDB);
			fwriteList(rank, &listDB, tmpArr);
			//파일을 닫습니다.
			fclose(rank);
			break;
		}
	}
	//메모리 할당 해제
	free(ans);
	free(user);
}