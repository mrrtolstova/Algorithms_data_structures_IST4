#ifndef HELPERS_H 
#define HELPERS_H 

#include <string> 
#include <vector>
#include <fstream> 

class FstreamHelper {
public:    
	/* Вспомогательная функция для чтения данных из файла и записи в матрицу.
	Возвращает true если считывание прошло       
	успешно. */     
	static bool ReadFileToStrings(std::string& theFilename, std::vector<std::string>& theStrings) {
	std::ifstream aFile(theFilename);         
	if (!aFile.is_open()) { return false;
	}

	std::string aFileLineString;

	// Считываем по одной строчке         
	while (getline (aFile, aFileLineString)) {         
		theStrings.push_back (aFileLineString);         } 

	aFile.close();

	return true;
}
};

#endif // HELPERS_H #pragma once
