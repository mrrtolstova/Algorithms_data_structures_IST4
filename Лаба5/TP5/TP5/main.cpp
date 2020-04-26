#include <iostream> 


using namespace std;
int N = 0;
void input(int* a) //проверка на ввод положительного числа
{
	while (!(std::cin >> *a) || *a <= 0)
	{
		std::cin.clear();
		std::cin.ignore(32267, '\n');
		std::cout << "Error" << std::endl;
	}
}
void create_lot(int stones[])   //создание массива весов камней 
{
	cout << N << " камней в куче. Их вес:\n";
	for (int i = 0; i < N; i++) {
		cout << (i + 1) << ": ";
		input(&stones[i]);
	}
}

void arrange_lot(int stones[])   //сортировка по убыванию 
{
	int i, j, cur;
	for (i = 0; i < N - 1; i++) {
		for (j = i + 1; j < N; j++) {
			if (stones[i] < stones[j]) {
				cur = stones[i];
				stones[i] = stones[j];
				stones[j] = cur;
			}
		}
	}
}

void arrange_heaps(int stones[])  //создание двух куч, как можно более близких по весу 
{
	int sum1 = 0, sum2 = 0, k1 = 0, k2 = 0, i;
	int *heap1 = new int[N-1];
	int* heap2 = new int[N-1];
	for (i = 0; i < N; i++) {
		if (sum1 <= sum2) {
			heap1[k1] = stones[i];
			sum1 += stones[i];
			k1++;
		}
		else {
			heap2[k2] = stones[i];
			sum2 += stones[i];
			k2++;
		}
	}
	if (1.0 * sum1 / sum2 <= 1.5) {
		cout << "\nКуча 1: ";
		for (i = 0; i < k1; i++)
			cout << heap1[i] << "  ";
		cout << "\nВес 1: " << sum1 << endl;
		cout << "\nКуча 2: ";
		for (i = 0; i < k2; i++)
			cout << heap2[i] << "  ";
		cout << "\nВес 2: " << sum2 << endl;
	}
	else cout << "Вес различается больше чем в 1,5 раза\n";
	delete[] heap1;
	delete[] heap2;
}

int main() {
	setlocale(LC_ALL, "");
	cout << "Введите количество камней:" << endl;
	input(&N);
	int* lot = new int[N];
	create_lot(lot);
	arrange_lot(lot);
	arrange_heaps(lot);
	delete[] lot; 
	return 0;
}

