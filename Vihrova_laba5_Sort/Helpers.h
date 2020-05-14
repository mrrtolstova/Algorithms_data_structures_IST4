#ifndef HELPERS_H 
#define HELPERS_H 

#include <string> 
#include <vector>
#include <fstream> 

class FstreamHelper {
public:    
	/* ��������������� ������� ��� ������ ������ �� ����� � ������ � �������.
	���������� true ���� ���������� ������       
	�������. */     
	static bool ReadFileToStrings(std::string& theFilename, std::vector<std::string>& theStrings) {
	std::ifstream aFile(theFilename);         
	if (!aFile.is_open()) { return false;
	}

	std::string aFileLineString;

	// ��������� �� ����� �������         
	while (getline (aFile, aFileLineString)) {         
		theStrings.push_back (aFileLineString);         } 

	aFile.close();

	return true;
}
};

#endif // HELPERS_H #pragma once
