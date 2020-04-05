#include <iostream> 

using namespace std;

//--- Функция "быстрой" сортировки ---\\ 
void quickSort(int arr[], int left, int right) 
{
	int i = left, j = right; // границы массива         
	int tmp; // переменная, временно хранящая в себе значения
	int pivot = arr[(left + right) / 2]; // нахождение середины массива 

	while (i <= j) { // пока не середина
		while (arr[i] < pivot) // пока значения слева меньше серединного
			i++;   
		while (arr[j] > pivot) // пока значения справа больше серединного
			j--;   
		if (i <= j) 
		{ 
			//--- Свап значений ---\\ 
			tmp = arr[i];    
			arr[i] = arr[j];    
			arr[j] = tmp;
			//--- ---\\ 
			i++;    
			j--; 
		} 
	}
	if (left < j)
		quickSort(arr, left, j); // вызов функции для левой части массива  
	if (i < right) 
		quickSort(arr, i, right); // вызов функции для правой части массива 
}
//--- ---\\

