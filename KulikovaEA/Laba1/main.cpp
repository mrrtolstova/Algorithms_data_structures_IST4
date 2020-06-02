#include <iostream>
#include <fstream>
#include <list>
#include <string>

int main(int argc, char * argv[]) 
{
	if (argc != 3)
		return -1; // Неверное количество параметров
	std::list<std::string> comments; // Список комментариев
	std::ifstream in; // Файл на чтение
	std::string line; // Строка для чтения
	int num; // Позиция //
	int num2; // Позиция /*
	int num3; // Позиция */
	bool flag = false; // Флаг для /* ... */
	bool flag2 = false; // Флаг для // ... /* ... */
	in.open(argv[1]);
	if (!in.is_open())
		return -2; // Файл на чтение не открыт
	while (getline(in, line)) 
	{
		num = line.find("//");
		while (num > -1) 
		{ // Считываем все //
			num2 = line.find("/*");
			num3 = line.find("*/", num2);
			// Для решения №15
			if (((num2 > num && num3 > num) || num2 == -1) && (!flag)) 
			{
				comments.push_back(line.substr(num));
				flag2 = true;
			}
			num = line.find("//", num + 2);
		}
		if (flag2) 
		{
			flag2 = false;
			continue;
		}
		if (flag) 
		{
			num3 = line.find("*/");
			if (num3 > -1) 
			{
				comments.push_back(line.substr(0, num3));
				flag = false;
			}
			else
				comments.push_back(line);
		}
		num2 = line.find("/*");
		while (num2 > -1) 
		{ // Для решения №1
			num3 = line.find("*/", num2 + 2);
			if (num3 > -1) 
				comments.push_back(line.substr(num2, num3 - num2));
			else 
			{
				comments.push_back(line.substr(num2));
				flag = true;
			}
			num2 = line.find("/*", num2 + 1);
		}
	}
	in.close();
	std::ofstream out;
	out.open(argv[2]);
	if (!out.is_open())
		return -3; // Файл для записи не открыт
	for (std::string n : comments)
		out << n << std::endl;
	out.close();
	comments.clear();
	return 0;
}
