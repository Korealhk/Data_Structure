
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

unsigned int data_count = 0;
unsigned int data_index = 0;

typedef struct Data {
	int index;
	char name[15];
	char phone[18];
	char address[50];
}data;

typedef struct node {
	data _data;
	struct node* prev;
	struct node* next;
}Node;

Node *head, *tail;

bool addNode(data _data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("주소록 추가에 실패 하였습니다. \n");
		return;
	}

	newNode->_data.index = _data.index;
	strcpy_s(newNode->_data.name, sizeof(newNode->_data.name), _data.name);
	strcpy_s(newNode->_data.phone, sizeof(newNode->_data.phone), _data.phone);
	strcpy_s(newNode->_data.address , sizeof(newNode->_data.address), _data.address);

	Node* cur = head->next;

	while (cur != NULL && cur->next != NULL && cur != tail && cur->_data.index < _data.index)
	{
		cur = cur->next;
	}

	Node* prev = cur->prev;
	prev->next = newNode;
	newNode->prev = prev;
	cur->prev = newNode;
	newNode->next = cur;

	return true;
}

bool addData()
{
	bool result = false;
	data _data;
	printf("****** 추가 ******\n\n\n");

	printf("인덱스 입력 : ");
	scanf_s("%d", &_data.index);
	fflush(stdin);
	getchar();

	printf("이름 입력 : ");
	fgets(_data.name, sizeof(_data.name), stdin);
	_data.name[strlen(_data.name) - 1] = '\0';

	printf("전화번호 입력 :");
	fgets(_data.phone, sizeof(_data.phone), stdin);
	_data.phone[strlen(_data.phone) - 1] = '\0';

	printf("주소입력 :");
	fgets(_data.address, sizeof(_data.address), stdin);
	_data.address[strlen(_data.address) - 1] = '\0';

	data_count = data_count + 1;

	result = addNode(_data);

	return true;
}



void Display(Node *ptr)
{
	ptr = ptr->next;
	printf("****** 보기 ******\n\n\n");

	while (ptr != tail)
	{
		printf("\n---------------------------------\n");
		printf("\n\n");
		printf("데이터 번호 : %d", ptr->_data.index);
		printf("\n\n");
		printf(" 이름 : ");
		printf("%-s", ptr->_data.name);
		printf("\n\n 전화 번호 :");
		printf("%-s", ptr->_data.phone);
		printf("\n\n 주소 : ");
		printf("%-s", ptr->_data.address);
		printf("\n\n");
		printf("\n---------------------------------\n");

		ptr = ptr->next;

		printf("\n");
	}

	printf("\n");
}

void SearchData()
{
	if (data_count == 0)
	{
		printf("조회할 데이터가 없습니다.\n");
		return;
	}

	int index;
	Node* searchNode;

	while (true) {
		printf("찾을 주소의 번호 입력 :");
		scanf_s("%d", &index);
		getchar();

		searchNode = head->next;

		while (searchNode->_data.index != index && searchNode != tail)
		{
			searchNode = searchNode->next;
		}

		if (searchNode == tail)
		{
			printf("\n\n 검색할번호는 없는 번호입니다. 다시 입력해주세요.\n\n\n");
		}
		else
		{
			printf("\n---------------------------------\n");
			printf("\n\n");
			printf("데이터 번호 : %d", searchNode->_data.index);
			printf("\n\n");
			printf(" 이름 : ");
			printf("%-s", searchNode->_data.name);
			printf("\n\n 전화 번호 :");
			printf("%-s", searchNode->_data.phone);
			printf("\n\n 주소 : ");
			printf("%-s", searchNode->_data.address);
			printf("\n\n");
			printf("\n---------------------------------\n");
			printf("\n");
			break;
		}
	}

	return;
}

void DeleteData()
{
	if (data_count == 0)
	{
		printf("삭제할 데이터가 없습니다.\n");
		return;
	}

	int index;
	printf("삭제할 주소의 번호 입력 :");
	scanf_s("%d", &index);
	getchar();

	Node* delNode = head->next;

	while (delNode->_data.index != index && delNode !=tail)
	{
		delNode = delNode->next;
	}

	if (delNode == tail)
	{
		printf("\n\n입력된 번호는 없는 주소입니다.\n\n");
		return;
	}

	Node* prev = delNode->prev;
	prev->next = delNode->next;
	prev->next->prev = prev;
	
	free(delNode);

	data_count = data_count - 1;

	printf("\n삭제 완료\n");

	return;
}

void main()
{
	int choice;

	head = (Node*)malloc(sizeof(Node));
	tail = (Node*)malloc(sizeof(Node));

	head->next = tail;
	tail->prev = head;

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
			if (addData())
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
			DeleteData();
			break;
		case '4':
			SearchData();
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