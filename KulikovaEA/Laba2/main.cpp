#include <iostream>
#include "CRS.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	unsigned int n; // Размер матрицы
	unsigned int nz = 0; // Количество ненулевых элементов
	double ** a; // Матрица вводимая пользователем
	std::cout << "Введите размер матрицы - ";
	std::cin >> n;
	std::cout << "Введите матрицу" << std::endl;
	a = new double*[n];
	for (unsigned i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (unsigned j = 0; j < n; j++)
		{
			std::cin >> a[i][j];
			if (j <= i && a[i][j] != 0)
				nz++;
		}
	}
	std::cout << std::endl;
	CRS A(a, n, nz); // Создание CRS представления матрицы
	A.Print(); // Печать представления CRS
	std::cout << std::endl << "Определитель - " << A.Determinant(a, n);
	return 0;
}
