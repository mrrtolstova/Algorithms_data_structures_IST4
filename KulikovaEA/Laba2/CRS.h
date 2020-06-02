#pragma once
#include <iostream>

class CRS
{
	double * adiag; // Массив значений по диагонали
	double * altr; // Массив остальных значений
	unsigned int * jptr; // Массив номеров столбцов элементов altr
	unsigned int * row_index; // Массив индексов строк
	unsigned int n; // Размер матрицы
	unsigned int nz; // Количество ненулевых элементов
public:
	CRS(double ** a, unsigned int _n, unsigned int _nz)
	{
		nz = _nz;
		n = _n;
		adiag = new double[n];
		altr = new double[nz - n];
		jptr = new unsigned int[nz - n];
		row_index = new unsigned int[n];
		unsigned int cur1 = 0;
		unsigned int cur2 = 0;
		for (unsigned i = 0; i < n; i++)
		{
			row_index[i] = cur2;
			for (unsigned j = 0; j < i + 1; j++)
			{
				if (i == j)
					adiag[cur1++] = a[i][j];
				else
				{
					if (a[i][j] != 0)
					{
						altr[cur2] = a[i][j];
						jptr[cur2++] = j;
					}
				}
			}
		}
	}
	~CRS() 
	{
		delete[] adiag;
		delete[] altr;
		delete[] jptr;
		delete[] row_index;
	}
	void Print()
	{// Представление разряженной симметричной матрицы в виде CRS
		std::cout << "Количество ненулевых элементов - " << nz << std::endl;
		std::cout << "Массив значений по диагонали:" << std::endl;
		for (unsigned i = 0; i < n; i++)
			std::cout << adiag[i] << " ";
		std::cout << std::endl << "Массив остальных значений:" << std::endl;
		for (unsigned i = 0; i < nz - n; i++)
			std::cout << altr[i] << " ";
		std::cout << std::endl << "Массив номеров столбцов недиагональных элементов:" << std::endl;
		for (unsigned i = 0; i < nz - n; i++)
			std::cout << jptr[i] << " ";
		std::cout << std::endl << "Массив индексов строк:" << std::endl;
		for (unsigned i = 0; i < n; i++)
			std::cout << row_index[i] << " ";
	}
	void GetMatr(double ** mas, double ** p, int i, int j, int m)
	{ // Получение матрицы без i-й строки и j-го столбца
		int ki, kj, di, dj;
		di = 0;
		for (ki = 0; ki < m - 1; ki++) 
		{ // проверка индекса строки
			if (ki == i) di = 1;
			dj = 0;
			for (kj = 0; kj < m - 1; kj++) 
			{ // проверка индекса столбца
				if (kj == j) dj = 1;
				p[ki][kj] = mas[ki + di][kj + dj];
			}
		}
	}
	double Determinant(double ** mas, int m)
	{ // Детерминант
		double ** p;
		p = new double*[m];
		for (int i = 0; i < m; i++)
			p[i] = new double[m];
		int k = 1;
		double d = 0;
		if (m == 1) 
			return mas[0][0];
		if (m == 2) 
			return mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
		if (m > 2) 
		{
			for (int i = 0; i < m; i++) 
			{
				GetMatr(mas, p, i, 0, m);
				d = d + k * mas[i][0] * Determinant(p, m - 1);
				k = -k;
			}
		}
		for (int i = 0; i < m; i++)
			delete[] p[i];
		delete[] p;
		return d;
	}
};

