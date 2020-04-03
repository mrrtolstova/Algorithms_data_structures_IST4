#include <iostream>

int * merge(int s1, int s2, int * m1, int * m2)
{
	int * res = new int[s1 + s2];
	int i = 0, j = 0, r = 0;
	while (i != s1 && j != s2)
	{
		if (m1[i] < m2[j])
			res[r++] = m1[i++];
		else
			res[r++] = m2[j++];
	}
	while (i < s1)
		res[r++] = m1[i++];
	while (j < s2)
		res[r++] = m2[j++];
	return res;
}

int main() 
{
	int n, m;
	std::cout << "size 1 - ";
	std::cin >> n;
	std::cout << "size 2 - ";
	std::cin >> m;
	int * mas1 = new int[n];
	int * mas2 = new int[m];
	std::cout << "massive 1 - ";
	for (int i = 0; i < n; i++)
		std::cin >> mas1[i];
	std::cout << "massive 2 - ";
	for (int i = 0; i < m; i++)
		std::cin >> mas2[i];
	int * res = merge(n, m, mas1, mas2);
	std::cout << "massive res - ";
	for (int i = 0; i < m + n; i++)
		std::cout << res[i] << " ";
	std::cin >> n;
}
