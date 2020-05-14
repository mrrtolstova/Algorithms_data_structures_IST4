#include <iostream> 
#include <string> 
#include <vector>
#include <wchar.h> 

#include "helpers.h" 

class InsertSort {
public:     
	/* Функция для сортировки вставками. */    
	static void Sort(int* const theMassive, const int theSize) {
	int aSortIndex = 0;

	while (aSortIndex < theSize - 1) 
	{ if (theMassive[aSortIndex] > theMassive[aSortIndex + 1]) 
	{ int anIndexToInsert = FindInsertIndex(theMassive, theSize, theMassive[aSortIndex + 1]);                 
	Insert(theMassive, anIndexToInsert, aSortIndex + 1); 
	}            
	++aSortIndex; }
}
private:     
	/* Вставляет значение из theMassive[thePreviousIndex] 
	в theMassive[theIndexToInsert] и выполняет сдвиг вправо. 
	*/     
	static void Insert(int* const theMassive, const int theIndexToInsert, const int thePreviousIndex) {
	int aTemp = theMassive[theIndexToInsert];

	theMassive[theIndexToInsert] = theMassive[thePreviousIndex];

	for (int i = thePreviousIndex; i > theIndexToInsert + 1; --i) 
	{ theMassive[i] = theMassive[i - 1]; }

	theMassive[theIndexToInsert + 1] = aTemp;
}

			 /* Ищет место для вставки. */     
	static int FindInsertIndex(const int* const theMassive, const int theSize, const int theValueToInsert)
	{ for (int i = 0; i < theSize; ++i) { 
		if (theValueToInsert < theMassive[i]) { return i; } }          
	std::cout << "Error" << std::endl;         
	return -1; }
};

class Anagram {
public:     Anagram(std::string& theWord) : myWord(theWord) { Sort(); }

			std::string GetWord() { return myWord; }

			std::string SortedSymbols() { return mySortedSymbols; }

private:     
	/* Сортируем символы и записываем полученную строку в поле mySortedSymbols. Для использования функции      
	* InsertSort::Sort создаем промежуточный сырой массив целых чисел.      
	*/     
	
	void Sort() {
		const int aMassiveSize = static_cast<int> (myWord.size());
		int *aMassive = new int[aMassiveSize];
	for (size_t i = 0; i < myWord.size(); ++i) {
		int anIndex = static_cast<int> (i); // приводим к числовому типу            
		aMassive[anIndex] = myWord[i];         }         
	InsertSort::Sort (aMassive, aMassiveSize); 
	// Сортируем числа 

		for (int i = 0; i < aMassiveSize; ++i) {
			mySortedSymbols.push_back(static_cast<char> (aMassive[i])); 
			// Приводим обратно к символьному типу        
		}     } 

			std::string myWord;    
			std::string mySortedSymbols;
		};

		/* Класс для поиска анаграмм. */ 
class AnagramFounder {
		public:     /* Функция создает объекты Anagram из строк переданного вектора theStrings.     
					* Объекты помещаются в собственный контейнер myAnagrams.      
					*/    
			void Init(std::vector<std::string>& theStrings) { 
				for (size_t i = 0; i < theStrings.size(); ++i) 
				{ myAnagrams.push_back(Anagram(theStrings[i])); 
				} }

					/* Функция вывода всех анаграмм. Использует массив флагов для избежания повторений.      
					* Для поиска анаграмм использует функцию Anagramm::SortedSymbols().     
					* Если отсортированный набор символов совпадает, то выводим слова используя функцию Anagramm::GetWord().      
					*/     
			void Print() {
						const int aMassiveSize = myAnagrams.size();        
						bool *anAlsoDisplayed = new bool[aMassiveSize];        
						for (int i = 0; i < aMassiveSize; ++i) { 
							anAlsoDisplayed[i] = false; 
						}

						for (int i = 0; i < aMassiveSize; ++i) {
							if (anAlsoDisplayed[i] == false) {

								anAlsoDisplayed[i] = true;

								size_t anIndex = static_cast<size_t> (i);

								std::cout << myAnagrams[anIndex].GetWord() << std::endl;
								for (size_t j = 0; j < myAnagrams.size(); ++j) {   
									
									// Сравниваем отсортированные строки                    
									if (!anAlsoDisplayed[j] && myAnagrams[anIndex].SortedSymbols() == myAnagrams[j].SortedSymbols()) {      
										anAlsoDisplayed[j] = true;                  
										std::cout << myAnagrams[j].GetWord() << std::endl;           
									}               
								}              
								std::cout << "----------------------" << std::endl;        
							}         
						} 


								} 
private:     
	std::vector<Anagram> myAnagrams;
							};

int main() {
     std::string aFilename = "dictionary.txt";   
     std::vector<std::string> aStrings;    
     bool aResult = FstreamHelper::ReadFileToStrings(aFilename, aStrings);   
     if (!aResult) {
		 std::cout << "Error reding from file. Check that file " << aFilename << " exist." << std::endl; 
	 }

      AnagramFounder aFounder;   
      aFounder.Init(aStrings);   
      aFounder.Print();

							
       std::cout << "_____" << std::endl;
	   system("pause");
							
 return 0;
							
}