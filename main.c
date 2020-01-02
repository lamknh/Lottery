#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 15 //최대 난수 크기 설정
#define NumberMax 3 // 숫자 선택 가능값
#define InputMax 15 //최대 로또 번호 입력 가능 사람 수
#define StringMax 300


struct Lottery
{
	char name[20]; //이름
	int num[NumberMax]; //숫자
	int correctNumber; //맞춘 갯수
}; //구조체 선언

void start(void); //시작 함수
void file_saving(struct Lottery List[]); //파일에 로또 번호 저장 함수
void lottery(struct Lottery List[]); //로또 추첨 함수
void winner(int arr[], struct Lottery List[]); //로또 당첨자 확인 함수

int main(void)
{
	printf("# # # # # # 간이 lotto 프로그램입니다 # # # # # #\n\n");
	printf("(로또 추첨은 이미 입력된 값을 이용하여 추첨됩니다)"); //프로그램 설명
	
	start(); //시작 함수 호출

	return 0;
}

void start(void) //시작 함수
{
	struct Lottery PplList[InputMax] = { "", 0, 0, 0, 0}; //구조체 초기화

	printf("\n로또 추첨을 시작한다면 y를 입력, 로또 번호를 입력하려면 n을 입력해주세요 :");

	char a; //Exception Handling 위한 변수 선언
	scanf_s("%c", &a, 1); //분기점 설정

	if (a == 'y')
	{
		lottery(PplList);
	} //로또 추첨 함수 호출
	else if (a == 'n')
	{
		printf("\n\n# # # 로또 번호 입력을 시작합니다 # # #\n\n");
		file_saving(PplList);
	} //로또 번호 저장 함수 호출
	else
	{
		printf("* * * 문자를 잘못 입력하셨습니다. 다시 입력해주세요. * * * \n\n");
		scanf_s("%c", &a, 1);
		start();
	}//Exception Handling

	return;
}

void file_saving(struct Lottery PplList[]) //파일에 로또 번호 저장 함수
{

	printf("'이름 번호1 번호2 번호3'의 형식으로 입력해주십시오: \n");
	printf("(이름은 되도록 영어로 작성해주십시오)\n");

	scanf_s("%s %d %d %d", &PplList->name, 20, &PplList->num[0], &PplList->num[1], &PplList->num[2]); //구조체 배열에 이름 및 로또 번호 입력받기

	if ((PplList->num[0] > MAX) || (PplList->num[1] > MAX) || (PplList->num[2] > MAX))
	{
		printf("\n숫자를 잘못 입력하셨습니다. 다시 시도해주세요\n\n");
		return;
	}//Exception Handling

	FILE* fp;
	errno_t err = fopen_s(&fp, "lotto_number.txt", "a");
	if (err) return;//파일 열기

	if (fp == NULL)
	{
		printf("파일 열기가 실패하였습니다");
		return;
	}//파일 불러오기 실패시 뜰 메세지 출력

	fprintf(fp, "%s %d %d %d\n", PplList->name, PplList->num[0], PplList->num[1], PplList->num[2]);//파일에 입력된 값 저장

	fclose(fp);//파일 닫기
		
	printf("====== 입력 성공! ======\n");//성공적으로 저장된 경우 뜨는 메세지 출력

	return;
}

void lottery(struct Lottery PplList[]) //로또 추첨 함수
{
	printf("\n\n# # # # # # # # # # # # # #  # # #\n");
	printf("# # # 로또 추첨을 시작합니다 # # #\n");
	printf("# # # # # # # # # # # # # #  # # #\n\n\n");

	int lottery_number[NumberMax] = {0};//로또 번호 배열 초기화

	srand(time(NULL)); // 매번 새로운 난수 발생시키기 위해

	for (int i = 0; i < NumberMax; i++)
	{
		lottery_number[i] = 1 + (rand() % MAX); // 1~15까지의 난수 범위 설정
		for (int j = 0; j < i; j++)
		{
			if (lottery_number[i] == lottery_number[j]) // 중복 피하기
			{
				lottery_number[i] = 1 + (rand() % MAX);
				i--;
			}
		}
	}//로또 번호 NumberMax가지 추첨

	printf("* * * 당첨 번호 : ");

	for (int i = 0; i < NumberMax; i++)
	{
		printf("%d ", lottery_number[i]);
	}//당첨 번호 출력

	printf("\n\n\n");
	winner(lottery_number, PplList); //당첨자 확인 함수 호출

	return;
}

void winner(int lottery_number[], struct Lottery PplList[]) //당첨자 확인 함수
{
	char first_list[StringMax] = { "" }, second_list[StringMax] = { "" }, third_list[StringMax] = { "" }; //1~3등까지 이름 저장할 배열 선언 및 초기화

	FILE* fp;
	errno_t err = fopen_s(&fp, "lotto_number.txt", "r");
	if (err) return; //저장된 파일 열기
	
	if (fp == NULL)
	{
		printf("파일 열기에 실패했습니다\n");
	}//파일 열기 실패시 뜰 경고문

	while (fscanf_s(fp, "%s %d %d %d", &PplList->name, 20, &PplList->num[0], &PplList->num[1], &PplList->num[2]) != EOF) //파일 끝날때 까지 반복
	{	
		PplList->correctNumber = 0; //맞춘 갯수를 넣는 구조체 항목 초기화

		for (int k = 0; k < InputMax; k++)
		{
			for (int i = 0; i < NumberMax; i++)
			{
				for (int j = 0; j < NumberMax; j++)
				{
					if (lottery_number[i] == PplList[k].num[j])
					{
						PplList[k].correctNumber += 1;//로또 번호와 값이 일치한다면 맞춘 개수 구조체 항목에 +1
					}
				}
			}
		}//로또 번호와 입력한 번호 비교

		for (int i = 0; i < InputMax; i++) //저장값 최대까지
		{
			switch (PplList[i].correctNumber)
			{
			case 1: //1개 맞춘 경우
				strcat_s(third_list, StringMax, PplList[i].name); //문자열에 추가
				strcat_s(third_list, StringMax, "/"); //이름 사이에 '/' 찍어주기
				break;
			case 2: //2개 맞춘 경우
				strcat_s(second_list, StringMax, PplList[i].name);
				strcat_s(second_list, StringMax, "/");
				break;
			case 3: //3개 맞춘 경우
				strcat_s(first_list, StringMax, PplList[i].name);
				strcat_s(first_list, StringMax, "/");
				break;
			default: //그 외
				break;
			}
		}
	}

	fclose(fp);

	printf("# # # 당첨자 발표 - 축하합니다 # # #\n\n");
	printf("1등: /%s\n", first_list);
	printf("2등: /%s\n", second_list);
	printf("3등: /%s\n", third_list);
	printf("\n# # # # # # # # # # # # # # # # # #\n\n"); //당첨자 발표

	return;
}