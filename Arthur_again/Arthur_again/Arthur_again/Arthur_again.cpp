#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

void Sort(int *mas) // сортировка "пузырьком"
{
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12 - i - 1; j++)
			if (abs(mas[j]) > abs(mas[j + 1]))
			{
				int a = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = a;
			}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	ifstream fin("data.txt");

	if (!fin.is_open()) // если файл не был открыт
	{
		cout << "Файл не может быть открыт или создан\n";
		return -1;
	}

	int *mas = new int[12];
	int zero = 0, positive = 0, negative = 0;

	int i = 0;
	for (int i = 0; i < 12; i++)
	{
		fin >> mas[i];
		if (mas[i] > 0)
			positive++;
		else if (mas[i] < 0)
			negative++;
		else
			zero++;
	}

	for (int i = 0; i < 12; i++)
		cout << mas[i] << endl;

	cout << "Число положительных элементов : " << positive << endl;
	cout << "Число отрицательных элементов : " << negative << endl;
	cout << "Число нулевых элементов : " << zero << endl;

	if (negative == 0 && zero == 0) // числа натуральные
	{
		Sort(mas);
		int Q = mas[0] * mas[11];
		for (int i = 1; i < 11; i++)
			if (Q != mas[i] * mas[12 - i - 1])
			{
				cout << "Разбить на пары нельзя" << endl;
				return 1;
			}
		for (int i = 0; i < 12 / 2; i++)
			cout << mas[i] << " * " << mas[12 - i - 1] << " = " << Q << endl;
	}
	else // числа целые
	{
		if (zero % 2 || negative % 2) // если колличество нулевых или отрицательных элементов нечетное, то пары составить нельзя
		{
			cout << "Разбить на пары нельзя" << endl;
			return 2;
		}
		else
		{
			Sort(mas);
			int Q = mas[0] * mas[11];
			for (int i = 1; i < 11; i++)
				if (Q != mas[i] * mas[12 - i - 1])
				{
					cout << "Разбить на пары нельзя" << endl;
					return 3;
				}
			for (int i = 0; i < 12 / 2; i++)
				cout << mas[i] << " * " << mas[12 - i - 1] << " = " << Q << endl;
		}
	}

	return 0;
}
