#include "stdafx.h"
#include <pthread.h>
#include <iostream>

using namespace std;

int mas[9] = { 1,2,3,4,5,6,7,8,9 };
int A, B, C;
int i, j, p = 2;
pthread_mutex_t mutex;struct result //��������� �������
{ //��� ������ ���������� ���������� � �������������� ����������
	char str[90];
	result *next; //��������� �� ��������� ������� �������
};result *head; //��������� �� ������ ������� �������
result *newrez; //���������/��� �������� ����� ��������� �������
result *rez; //��������� �� ������� ��������� ������� �������
void *massiv(void *arg)
{
	int x = 0;
	int ind = *(int *)arg;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = ind; k < 9; k = k + p)
			{
				for (int z = 0; z < 9; z++)
				{
					if (mas[i] == A*mas[j] + B*mas[k] + C*mas[z])
					{
						pthread_mutex_lock(&mutex); /*�������� ����� � ��: �������
													�������� �������*/

						newrez = new result; //������ ����������� ������ � ������ ���������� � �������
						cout << "�������� ����� �: " << ind << ". ��������, ��� ������� ��������� �����������:\n" << mas[i] << mas[j] << mas[k] << mas[z] << "\n";
						sprintf_s(newrez->str, "%d = %d %d %d ", mas[i], mas[j], mas[k], mas[z]);
						newrez->next = NULL;
						rez->next = newrez;
						rez = newrez;
						pthread_mutex_unlock(&mutex); /*�������� ������ �� ��:
													  ������� �������� �������*/
													  //����� ����������� ������
					}
				}
			}
		}
	}

	return(void *)x;
}


int main()
{
	head = new result; rez = head; //�������� ������� �������� �������
	pthread_mutex_init(&mutex, NULL); //������������� ��������� ��������

	int *arg;
	arg = new int[p];
	pthread_t thread[2]; int number[2];
	cin >> A >> B >> C;
	//�������� ���� �������� �������
	for (int i = 0; i<2; i++)
	{
		number[i] = i; //��� �������� ��������� ������
		pthread_create(&thread[i], NULL, massiv, (void *)(number + i));
	}
	for (int i = 0; i<2; i++)
	{ //�������� ���������� ������ �������� �������
	  //� ��������� ���������� �� ����������
		pthread_join(thread[i], NULL);
	}
	rez = head->next;
	while (rez != NULL)
	{
		fprintf(stdout, "\n%s", rez->str); rez = rez->next;
	}
	system("pause");
	return 0;
}

