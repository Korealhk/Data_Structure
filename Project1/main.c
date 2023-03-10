
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

unsigned int data_count = 0;
unsigned int data_index = 0;

typedef struct Data {
	int index;
	char name[15];
	char phone[18];
	char address[50];

	struct Data *link;
}data;

void initdata(data *ptr)
{
	ptr->index = 0;
	strcpy_s(ptr->name, sizeof(ptr->name),"");
	strcpy_s(ptr->phone, sizeof(ptr->phone),"");
	strcpy_s(ptr->address, sizeof(ptr->address),"");
	ptr->link = NULL;
}

bool addData(data *ptr)
{
	while (ptr->link != NULL)
		ptr = ptr->link;

	ptr->link = (data*)malloc(sizeof(data));

	if (ptr->link == NULL)
	{
		printf("\n\n 시스템 메모리 부족으로 인하여 추가 작업이 실패하였습니다. \n\n");
		return false;
	}

	ptr = ptr->link;

	printf("****** 추가 ******\n\n\n");

	printf("이름 입력 : ");
	fgets(ptr->name, sizeof(ptr->name), stdin);
	ptr->name[strlen(ptr->name) - 1] = '\0';

	printf("전화번호 입력 :");
	fgets(ptr->phone, sizeof(ptr->phone), stdin);
	ptr->phone[strlen(ptr->phone) - 1] = '\0';

	printf("주소입력 :");
	fgets(ptr->address, sizeof(ptr->address), stdin);
	ptr->address[strlen(ptr->address) - 1] = '\0';

	ptr->link = NULL;

	data_count = data_count + 1;
	data_index = data_index + 1;
	ptr->index = data_index;

	return true;
}

void Display(data *ptr)
{
	ptr = ptr->link;
	printf("****** 보기 ******\n\n\n");

	while (ptr != NULL)
	{
		printf("\n---------------------------------\n");
		printf("\n\n");
		printf("데이터 번호 : %d", ptr->index);
		printf("\n\n");
		printf(" 이름 : ");
		printf("%-s", ptr->name);
		printf("\n\n 전화 번호 :");
		printf("%-s", ptr->phone);
		printf("\n\n 주소 : ");
		printf("%-s", ptr->address);
		printf("\n\n");
		printf("\n---------------------------------\n");

		ptr = ptr->link;

		printf("\n");
	}

	printf("\n");
}

void SearchData(data *ptr)
{
	char name[15];
	printf("****** 검색 ******\n\n\n");

	printf("검색할 사람의 이름 : ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';

	while (ptr->link != NULL)
	{
		ptr = ptr->link;

		if (strcmp(ptr->name, name) == 0)
		{
			printf("\n ---- 검색 결과 ---- \n\n");
			printf("이름 : %s", ptr->name);
			printf("\n\n");
			printf("전화번호 : %s", ptr->phone);
			printf("\n\n");
			printf("주소 : %s", ptr->address);
			printf("\n\n");
			printf("-------------------------------------");
			printf("\n\n");
			break;
		}

		if (ptr->link == NULL)
		{
			printf("\n %s로 등록된 데이터가 없습니다.\n", name);
		}
	}

	return;
}

void DeleteData(data *ptr)
{
	data *temp = NULL;
	bool flag = false;
	char name[15];
	printf("****** 삭제 ******\n\n\n");
	printf("삭제 할 사람의 이름 : ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';

	while (ptr->link != NULL)
	{
		temp = ptr;
		ptr = ptr->link;

		if (strcmp(name, ptr->name) == 0)
		{
			flag = true;
			temp->link = ptr->link;
			free(ptr);

			printf("\n\n삭제 완료\n");
			data_count = data_count - 1;
			break;
		}

		if (ptr->link == NULL)
		{
			printf("\n %s로 등록된 데이터가 없습니다.\n", name);
		}
	}

	

	return;
}


void main()
{
	data *head = NULL;
	int choice;

	head = (data*)malloc(sizeof(data));

	initdata(head);

	do {
		printf("\n\n");
		printf("\n\n");
		printf("****** 주소록 ******\n\n\n");
		printf("--------------------\n\n");
		printf("현재 등록된 주소의 수 %d", data_count);
		printf("\n\n--------------------\n\n");

		printf("1. 추가 \n\n");
		printf("2. 보기 \n\n");
		printf("3. 삭제 \n\n");
		printf("4. 검색 \n\n");
		printf("5. 종료 \n\n");

		printf("\n 입력 : ");
		choice = getchar();

		while (getchar() != '\n');

		fflush(stdin);

		printf("\n\n");
		switch (choice)
		{
		case '1':
			if (addData(head))
			{
				printf("\n\n성공\n\n");
			}
			else
			{
				printf("\n\n실패\n\n");
			}
			break;
		case '2':
			Display(head);
			break;
		case '3':
			DeleteData(head);
			break;
		case '4':
			SearchData(head);
			break;
		case '5':
			printf("종료\n");
			break;
		default:
			printf("잘못입력 \n");
			break;
		}
	} while (choice != '5');
}