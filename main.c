#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 15 //�ִ� ���� ũ�� ����
#define NumberMax 3 // ���� ���� ���ɰ�
#define InputMax 15 //�ִ� �ζ� ��ȣ �Է� ���� ��� ��
#define StringMax 300


struct Lottery
{
	char name[20]; //�̸�
	int num[NumberMax]; //����
	int correctNumber; //���� ����
}; //����ü ����

void start(void); //���� �Լ�
void file_saving(struct Lottery List[]); //���Ͽ� �ζ� ��ȣ ���� �Լ�
void lottery(struct Lottery List[]); //�ζ� ��÷ �Լ�
void winner(int arr[], struct Lottery List[]); //�ζ� ��÷�� Ȯ�� �Լ�

int main(void)
{
	printf("# # # # # # ���� lotto ���α׷��Դϴ� # # # # # #\n\n");
	printf("(�ζ� ��÷�� �̹� �Էµ� ���� �̿��Ͽ� ��÷�˴ϴ�)"); //���α׷� ����
	
	start(); //���� �Լ� ȣ��

	return 0;
}

void start(void) //���� �Լ�
{
	struct Lottery PplList[InputMax] = { "", 0, 0, 0, 0}; //����ü �ʱ�ȭ

	printf("\n�ζ� ��÷�� �����Ѵٸ� y�� �Է�, �ζ� ��ȣ�� �Է��Ϸ��� n�� �Է����ּ��� :");

	char a; //Exception Handling ���� ���� ����
	scanf_s("%c", &a, 1); //�б��� ����

	if (a == 'y')
	{
		lottery(PplList);
	} //�ζ� ��÷ �Լ� ȣ��
	else if (a == 'n')
	{
		printf("\n\n# # # �ζ� ��ȣ �Է��� �����մϴ� # # #\n\n");
		file_saving(PplList);
	} //�ζ� ��ȣ ���� �Լ� ȣ��
	else
	{
		printf("* * * ���ڸ� �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���. * * * \n\n");
		scanf_s("%c", &a, 1);
		start();
	}//Exception Handling

	return;
}

void file_saving(struct Lottery PplList[]) //���Ͽ� �ζ� ��ȣ ���� �Լ�
{

	printf("'�̸� ��ȣ1 ��ȣ2 ��ȣ3'�� �������� �Է����ֽʽÿ�: \n");
	printf("(�̸��� �ǵ��� ����� �ۼ����ֽʽÿ�)\n");

	scanf_s("%s %d %d %d", &PplList->name, 20, &PplList->num[0], &PplList->num[1], &PplList->num[2]); //����ü �迭�� �̸� �� �ζ� ��ȣ �Է¹ޱ�

	if ((PplList->num[0] > MAX) || (PplList->num[1] > MAX) || (PplList->num[2] > MAX))
	{
		printf("\n���ڸ� �߸� �Է��ϼ̽��ϴ�. �ٽ� �õ����ּ���\n\n");
		return;
	}//Exception Handling

	FILE* fp;
	errno_t err = fopen_s(&fp, "lotto_number.txt", "a");
	if (err) return;//���� ����

	if (fp == NULL)
	{
		printf("���� ���Ⱑ �����Ͽ����ϴ�");
		return;
	}//���� �ҷ����� ���н� �� �޼��� ���

	fprintf(fp, "%s %d %d %d\n", PplList->name, PplList->num[0], PplList->num[1], PplList->num[2]);//���Ͽ� �Էµ� �� ����

	fclose(fp);//���� �ݱ�
		
	printf("====== �Է� ����! ======\n");//���������� ����� ��� �ߴ� �޼��� ���

	return;
}

void lottery(struct Lottery PplList[]) //�ζ� ��÷ �Լ�
{
	printf("\n\n# # # # # # # # # # # # # #  # # #\n");
	printf("# # # �ζ� ��÷�� �����մϴ� # # #\n");
	printf("# # # # # # # # # # # # # #  # # #\n\n\n");

	int lottery_number[NumberMax] = {0};//�ζ� ��ȣ �迭 �ʱ�ȭ

	srand(time(NULL)); // �Ź� ���ο� ���� �߻���Ű�� ����

	for (int i = 0; i < NumberMax; i++)
	{
		lottery_number[i] = 1 + (rand() % MAX); // 1~15������ ���� ���� ����
		for (int j = 0; j < i; j++)
		{
			if (lottery_number[i] == lottery_number[j]) // �ߺ� ���ϱ�
			{
				lottery_number[i] = 1 + (rand() % MAX);
				i--;
			}
		}
	}//�ζ� ��ȣ NumberMax���� ��÷

	printf("* * * ��÷ ��ȣ : ");

	for (int i = 0; i < NumberMax; i++)
	{
		printf("%d ", lottery_number[i]);
	}//��÷ ��ȣ ���

	printf("\n\n\n");
	winner(lottery_number, PplList); //��÷�� Ȯ�� �Լ� ȣ��

	return;
}

void winner(int lottery_number[], struct Lottery PplList[]) //��÷�� Ȯ�� �Լ�
{
	char first_list[StringMax] = { "" }, second_list[StringMax] = { "" }, third_list[StringMax] = { "" }; //1~3����� �̸� ������ �迭 ���� �� �ʱ�ȭ

	FILE* fp;
	errno_t err = fopen_s(&fp, "lotto_number.txt", "r");
	if (err) return; //����� ���� ����
	
	if (fp == NULL)
	{
		printf("���� ���⿡ �����߽��ϴ�\n");
	}//���� ���� ���н� �� ���

	while (fscanf_s(fp, "%s %d %d %d", &PplList->name, 20, &PplList->num[0], &PplList->num[1], &PplList->num[2]) != EOF) //���� ������ ���� �ݺ�
	{	
		PplList->correctNumber = 0; //���� ������ �ִ� ����ü �׸� �ʱ�ȭ

		for (int k = 0; k < InputMax; k++)
		{
			for (int i = 0; i < NumberMax; i++)
			{
				for (int j = 0; j < NumberMax; j++)
				{
					if (lottery_number[i] == PplList[k].num[j])
					{
						PplList[k].correctNumber += 1;//�ζ� ��ȣ�� ���� ��ġ�Ѵٸ� ���� ���� ����ü �׸� +1
					}
				}
			}
		}//�ζ� ��ȣ�� �Է��� ��ȣ ��

		for (int i = 0; i < InputMax; i++) //���尪 �ִ����
		{
			switch (PplList[i].correctNumber)
			{
			case 1: //1�� ���� ���
				strcat_s(third_list, StringMax, PplList[i].name); //���ڿ��� �߰�
				strcat_s(third_list, StringMax, "/"); //�̸� ���̿� '/' ����ֱ�
				break;
			case 2: //2�� ���� ���
				strcat_s(second_list, StringMax, PplList[i].name);
				strcat_s(second_list, StringMax, "/");
				break;
			case 3: //3�� ���� ���
				strcat_s(first_list, StringMax, PplList[i].name);
				strcat_s(first_list, StringMax, "/");
				break;
			default: //�� ��
				break;
			}
		}
	}

	fclose(fp);

	printf("# # # ��÷�� ��ǥ - �����մϴ� # # #\n\n");
	printf("1��: /%s\n", first_list);
	printf("2��: /%s\n", second_list);
	printf("3��: /%s\n", third_list);
	printf("\n# # # # # # # # # # # # # # # # # #\n\n"); //��÷�� ��ǥ

	return;
}