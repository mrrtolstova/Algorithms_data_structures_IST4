#include <iostream>
#include <fstream>
#include <vector>
#include <set>

typedef std::vector<std::vector<int>> Puzzle;
typedef std::set<int> Values;

int size;

class ABCSolver 
{
public:
	static Puzzle solve(const Puzzle& puzzle, const Puzzle& info)
	{// Поиск решения
		Puzzle solution = puzzle;
		if (solveHelper(&solution, info))
			return solution;
		return Puzzle();
	}

	static bool solveHelper(Puzzle* solution, const Puzzle& info)
	{
		int minRow = -1;
		int minColumn = -1;
		Values minValues;
		while (true) 
		{
			minRow = -1;
			for (int i = 0; i < size; i++) 
			{
				for (int j = 0; j < size; j++) 
				{
					if ((*solution)[i][j] != 0)
						continue;
					Values possibleValues = findPossibleValues(i, j, *solution, info);
					int possibleVaueCount = possibleValues.size();
					if (possibleVaueCount == 0)
						return false;
					if (possibleVaueCount == 1)
						(*solution)[i][j] = *possibleValues.begin();
					if (minRow < 0 || possibleVaueCount < minValues.size()) 
					{
						minRow = i;
						minColumn = j;
						minValues = possibleValues;
					}
				}
			}
			if (minRow == -1)
				return true;
			else if (1 < minValues.size())
				break;
		}
		for (auto v : minValues) 
		{
			Puzzle solutionCopy = *solution;
			solutionCopy[minRow][minColumn] = v;
			if (solveHelper(&solutionCopy, info)) 
			{
				*solution = solutionCopy;
				return true;
			}
		}
		return false;
	}

	static Values findPossibleValues(int rowIndex, int columnIndex, const Puzzle& puzzle, const Puzzle& info)
	{// Получить возможные значения
		Values values;
		for (int i = 1; i < size + 1; i++)
			values.insert(i);
		Values del;
		del = getRowValues(rowIndex, columnIndex, puzzle, info);
		for (auto d : del)
			values.erase(d);
		del = getColumnValues(rowIndex, columnIndex, puzzle, info);
		for (auto d : del)
			values.erase(d);
		if (values.size() == 1 && *values.begin() == size)
		{
			if (rowIndex == 0)
			{
				if (puzzle[rowIndex + 1][columnIndex] && info[0][columnIndex])
				{
					if (puzzle[rowIndex + 1][columnIndex] != info[0][columnIndex])
						return Values();
				}
			}
			if (rowIndex == size - 1)
			{
				if (puzzle[rowIndex - 1][columnIndex] && info[1][columnIndex])
				{
					if (puzzle[rowIndex - 1][columnIndex] != info[1][columnIndex])
						return Values();
				}
			}
			if (columnIndex == 0)
			{
				if (puzzle[rowIndex][columnIndex + 1] && info[2][columnIndex])
				{
					if (puzzle[rowIndex][columnIndex + 1] != info[2][columnIndex])
						return Values();
				}
			}
			if (columnIndex == size - 1)
			{
				if (puzzle[rowIndex][columnIndex - 1] && info[3][columnIndex])
				{
					if (puzzle[rowIndex][columnIndex - 1] != info[3][columnIndex])
						return Values();
				}
			}
		}
		return values;
	}

	static Values getRowValues(int rowIndex, int columnIndex, const Puzzle& puzzle, const Puzzle& info)
	{// Получить исключаемые значения для строк
		Values values;
		if (info[2][rowIndex] && columnIndex < 2)
		{
			if (columnIndex == 0 || puzzle[rowIndex][0] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[2][rowIndex]);
			}
		}
		if (info[3][rowIndex] && columnIndex > (size - 3))
		{
			if (columnIndex == (size - 1) || puzzle[rowIndex][size - 1] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[3][rowIndex]);
			}
		}
		for (int r = 0; r < size; r++)
		{
			if (puzzle[rowIndex][r] > 0)
			{
				values.insert(puzzle[rowIndex][r]);
			}
		}
		return values;
	}

	static Values getColumnValues(int rowIndex, int columnIndex, const Puzzle& puzzle, const Puzzle& info)
	{// Получить исключаемые значения для столбцов
		Values values;
		if (info[0][columnIndex] && rowIndex < 2)
		{
			if (rowIndex == 0 || puzzle[0][columnIndex] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[0][columnIndex]);
			}
		}
		if (info[1][columnIndex] && rowIndex > (size - 3))
		{
			if (rowIndex == (size - 1) || puzzle[size - 1][columnIndex] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[1][columnIndex]);
			}
		}
		for (int r = 0; r < size; r++)
		{
			if (puzzle[r][columnIndex] > 0)
				values.insert(puzzle[r][columnIndex]);
		}
		return values;
	}
};

void printPuzzle(const Puzzle& puzzle, const Puzzle& info) 
{// Печатает игровое поле
	std::cout << "  ";
	for (int i = 0; i < size; i++)
	{
		if (info[0][i])
			std::cout << (char)(info[0][i] + 64) << " ";
		else
			std::cout << "  ";
	}
	std::cout << std::endl;
	for (int i = 0; i < size; i++) 
	{
		if (info[2][i])
			std::cout << (char)(info[2][i] + 64) << " ";
		else
			std::cout << "  ";
		for (int j = 0; j < size; j++) 
		{
			if (puzzle[i][j] == size)
				std::cout << "X ";
			else
				std::cout << (char)(puzzle[i][j] + 64) << " ";
		}
		if (info[3][i])
			std::cout << (char)(info[3][i] + 64);
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (int i = 0; i < size; i++)
	{
		if (info[1][i])
			std::cout << (char)(info[1][i] + 64) << " ";
		else
			std::cout << "  ";
	}
	std::cout << std::endl;
}

int main() 
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

	// Чтение из файла
	char c;
	in >> size;
	Puzzle puzzle(size);
	for (int i = 0; i < size; i++)
	{// Чтение доски
		for (int j = 0; j < size; j++)
		{
			in >> c;
			puzzle[i].push_back((int)c - 64);
		}
	}
	Puzzle info(4);
	for (int i = 0; i < 4; i++)
	{// Чтение боковой информации
		for (int j = 0; j < size; j++)
		{
			in >> c;
			info[i].push_back((int)c - 64);
		}
	}

	printPuzzle(puzzle, info);
	std::cout << std::endl;

	Puzzle solution = ABCSolver::solve(puzzle, info);
	if (!solution.empty())
	{// Если решение найдено
		printPuzzle(solution, info);
		// Запись в файл
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				out << solution[i][j] << " ";
			out << std::endl;
		}
	}
	else
		std::cout << "There's no solution" << std::endl;

	in.close();
	out.close();
	return 0;
}
