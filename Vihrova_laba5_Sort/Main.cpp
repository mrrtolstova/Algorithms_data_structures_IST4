#include <iostream> 
#include <string> 
#include <vector>
#include <wchar.h> 

#include "helpers.h" 

class InsertSort {
public:     
	/* ������� ��� ���������� ���������. */    
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
	/* ��������� �������� �� theMassive[thePreviousIndex] 
	� theMassive[theIndexToInsert] � ��������� ����� ������. 
	*/     
	static void Insert(int* const theMassive, const int theIndexToInsert, const int thePreviousIndex) {
	int aTemp = theMassive[theIndexToInsert];

	theMassive[theIndexToInsert] = theMassive[thePreviousIndex];

	for (int i = thePreviousIndex; i > theIndexToInsert + 1; --i) 
	{ theMassive[i] = theMassive[i - 1]; }

	theMassive[theIndexToInsert + 1] = aTemp;
}

			 /* ���� ����� ��� �������. */     
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
	/* ��������� ������� � ���������� ���������� ������ � ���� mySortedSymbols. ��� ������������� �������      
	* InsertSort::Sort ������� ������������� ����� ������ ����� �����.      
	*/     
	
	void Sort() {
		const int aMassiveSize = static_cast<int> (myWord.size());
		int *aMassive = new int[aMassiveSize];
	for (size_t i = 0; i < myWord.size(); ++i) {
		int anIndex = static_cast<int> (i); // �������� � ��������� ����            
		aMassive[anIndex] = myWord[i];         }         
	InsertSort::Sort (aMassive, aMassiveSize); 
	// ��������� ����� 

		for (int i = 0; i < aMassiveSize; ++i) {
			mySortedSymbols.push_back(static_cast<char> (aMassive[i])); 
			// �������� ������� � ����������� ����        
		}     } 

			std::string myWord;    
			std::string mySortedSymbols;
		};

		/* ����� ��� ������ ��������. */ 
class AnagramFounder {
		public:     /* ������� ������� ������� Anagram �� ����� ����������� ������� theStrings.     
					* ������� ���������� � ����������� ��������� myAnagrams.      
					*/    
			void Init(std::vector<std::string>& theStrings) { 
				for (size_t i = 0; i < theStrings.size(); ++i) 
				{ myAnagrams.push_back(Anagram(theStrings[i])); 
				} }

					/* ������� ������ ���� ��������. ���������� ������ ������ ��� ��������� ����������.      
					* ��� ������ �������� ���������� ������� Anagramm::SortedSymbols().     
					* ���� ��������������� ����� �������� ���������, �� ������� ����� ��������� ������� Anagramm::GetWord().      
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
									
									// ���������� ��������������� ������                    
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