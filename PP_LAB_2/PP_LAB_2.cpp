#include "stdafx.h"
#include <pthread.h>
#include <iostream>

using namespace std;

int mas[9] = { 1,2,3,4,5,6,7,8,9 };
int A, B, C;
int i, j, p = 2;
pthread_mutex_t mutex;struct result //структура очереди
{ //для записи результата вычислений и дополнительной информации
	char str[90];
	result *next; //указатель на следующий элемент очереди
};result *head; //указатель на первый элемент очереди
result *newrez; //указатель/для создания новых элементов очереди
result *rez; //указатель на текущий последний элемент очереди
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
						pthread_mutex_lock(&mutex); /*протокол входа в КС: закрыть
													двоичный семафор*/

						newrez = new result; //начало критической секции – запись результата в очередь
						cout << "Вычислил поток №: " << ind << ". Четверка, при которой равенство выполняется:\n" << mas[i] << mas[j] << mas[k] << mas[z] << "\n";
						sprintf_s(newrez->str, "%d = %d %d %d ", mas[i], mas[j], mas[k], mas[z]);
						newrez->next = NULL;
						rez->next = newrez;
						rez = newrez;
						pthread_mutex_unlock(&mutex); /*протокол выхода из КС:
													  открыть двоичный семафор*/
													  //конец критической секции
					}
				}
			}
		}
	}

	return(void *)x;
}


int main()
{
	head = new result; rez = head; //создание первого элемента очереди
	pthread_mutex_init(&mutex, NULL); //инициализация двоичного семафора

	int *arg;
	arg = new int[p];
	pthread_t thread[2]; int number[2];
	cin >> A >> B >> C;
	//создание двух дочерних потоков
	for (int i = 0; i<2; i++)
	{
		number[i] = i; //для передачи параметра потоку
		pthread_create(&thread[i], NULL, massiv, (void *)(number + i));
	}
	for (int i = 0; i<2; i++)
	{ //ожидание завершения работы дочерних потоков
	  //и получение результата их вычислений
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

