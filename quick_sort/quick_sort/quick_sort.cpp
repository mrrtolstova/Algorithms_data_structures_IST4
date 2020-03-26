#include <iostream> 
#include "quick_sort.h" 

using namespace std;

//--- Вывод на экран ---\\ 
void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "|";
	}
	cout << endl;
}
//--- ---\\

int main()
{
	int n; // размер массива
	cout << "Array Size: ";
	//--- Обработка ввода ---\\\ 
	while (!(cin >> n) || n < 0)
	{
		cout << "Uncorrect size, try again \n";
		cout << "Array Size: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << endl; 
	//--- ---\\\

	int* arr = new int[n]; // массив размером n
	//--- Ввод n элементов массив поочереди ---\\ 
	for (int i = 0; i < n; i++)
	{
		cout << "Array[" << i + 1 << "]: ";
		cin >> arr[i];
		cout << endl;
	}
	//--- ---\\ 

	print(arr, n); // вывод на экран введенной последовательности
	quickSort(arr, 0, n - 1); // функция сортировки
	print(arr, n); // вывод на экран результата сортировки
	system("pause");
}

