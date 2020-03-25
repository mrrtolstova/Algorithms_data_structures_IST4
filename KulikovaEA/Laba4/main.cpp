#include <iostream>
#include <fstream>
#include <vector>
#include <set>

typedef std::vector<std::vector<int>> Puzzle;
typedef std::set<int> Values;

int size;

// Класс решатель головоломки Easy as ABC
class ABCSolver 
{
public:
	// Поиск решения
	static Puzzle solve(const Puzzle& puzzle, const Puzzle& info)
	{
		Puzzle solution = puzzle;
		if (solveHelper(&solution, info))
			return solution;
		return Puzzle();
	}

	// Вспомогательная функция поиска решения
	static bool solveHelper(Puzzle* solution, const Puzzle& info)
	{
		int minRow = -1;
		int minColumn = -1;
		Values minValues;
		while (true) 
		{// Пока возможно
			minRow = -1;
			for (int i = 0; i < size; i++) 
			{
				for (int j = 0; j < size; j++) 
				{
					if ((*solution)[i][j] != 0)
						continue;
					// Для каждой клетки ищем возможные значения
					Values possibleValues = findPossibleValues(i, j, *solution, info);
					int possibleVaueCount = possibleValues.size();
					// Если для какой-то клетки подходящего значения не нашлось, то завершаем работу алгоритма (решения нет)
					if (possibleVaueCount == 0)
						return false;
					// Если существует единственное подходящее значение, то заполняем клетку соответствующим образом
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
			// Если все клетки заполнены, то завершаем цикл и возвращаем найденное решение
			if (minRow == -1)
				return true;
			// Иначе если ни одну клетку за проход заполнить не удалось, то завершаем цикл
			else if (1 < minValues.size())
				break;
		}
		for (auto v : minValues) 
		{// Для клетки с минимальным количеством вариантов
			Puzzle solutionCopy = *solution;
			// Пробуем ставить каждое значение по порядку и рекурсивно решать
			solutionCopy[minRow][minColumn] = v;
			if (solveHelper(&solutionCopy, info)) 
			{// Если решение было найдено, то возвращаем его
				*solution = solutionCopy;
				return true;
			}
		}
		// Решение не найдено
		return false;
	}

	// Получить возможные значения
	static Values findPossibleValues(int rowIndex, int columnIndex, const Puzzle& puzzle, const Puzzle& info)
	{
		Values values;
		// Исходно возможны все значения
		for (int i = 1; i < size + 1; i++)
			values.insert(i);
		Values del;
		// Ищем исключения анализируя строки
		del = getRowValues(rowIndex, columnIndex, puzzle, info);
		for (auto d : del)
			values.erase(d);
		// Ищем исключения анализируя столбцы
		del = getColumnValues(rowIndex, columnIndex, puzzle, info);
		for (auto d : del)
			values.erase(d);
		if (values.size() == 1 && *values.begin() == size)
		{// Особый случай - если возможное значение только "X"
			if (rowIndex == 0)
				if (puzzle[rowIndex + 1][columnIndex] && info[0][columnIndex])
					if (puzzle[rowIndex + 1][columnIndex] != info[0][columnIndex])
						return Values();
			if (rowIndex == size - 1)
				if (puzzle[rowIndex - 1][columnIndex] && info[1][columnIndex])
					if (puzzle[rowIndex - 1][columnIndex] != info[1][columnIndex])
						return Values();
			if (columnIndex == 0)
				if (puzzle[rowIndex][columnIndex + 1] && info[2][columnIndex])
					if (puzzle[rowIndex][columnIndex + 1] != info[2][columnIndex])
						return Values();
			if (columnIndex == size - 1)
				if (puzzle[rowIndex][columnIndex - 1] && info[3][columnIndex])
					if (puzzle[rowIndex][columnIndex - 1] != info[3][columnIndex])
						return Values();
		}
		return values;
	}

	// Получить исключаемые значения для строк
	static Values getRowValues(int rowIndex, int columnIndex, const Puzzle& puzzle, const Puzzle& info)
	{
		Values values;
		if (info[2][rowIndex] && columnIndex < 2)
		{// Если информационный левый столбец имеет значение
			if (columnIndex == 0 || puzzle[rowIndex][0] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[2][rowIndex]);
			}
		}
		if (info[3][rowIndex] && columnIndex > (size - 3))
		{// Если информационный правый столбец имеет значение
			if (columnIndex == (size - 1) || puzzle[rowIndex][size - 1] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[3][rowIndex]);
			}
		}
		// Если в строке уже есть значения
		for (int r = 0; r < size; r++)
			if (puzzle[rowIndex][r] > 0)
				values.insert(puzzle[rowIndex][r]);
		return values;
	}

	// Получить исключаемые значения для столбцов
	static Values getColumnValues(int rowIndex, int columnIndex, const Puzzle& puzzle, const Puzzle& info)
	{
		Values values;
		if (info[0][columnIndex] && rowIndex < 2)
		{// Если информационная верхняя строка имеет значение
			if (rowIndex == 0 || puzzle[0][columnIndex] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[0][columnIndex]);
			}
		}
		if (info[1][columnIndex] && rowIndex > (size - 3))
		{// Если информационная нижняя строка имеет значение
			if (rowIndex == (size - 1) || puzzle[size - 1][columnIndex] == size)
			{
				for (int i = 1; i < size; i++)
					values.insert(i);
				values.erase(info[1][columnIndex]);
			}
		}
		// Если в столбце уже есть значения
		for (int r = 0; r < size; r++)
			if (puzzle[r][columnIndex] > 0)
				values.insert(puzzle[r][columnIndex]);
		return values;
	}
};

// Печатает игровое поле
void printPuzzle(const Puzzle& puzzle, const Puzzle& info) 
{
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
			{
				if (solution[i][j] == size)
					out << "X ";
				else
					out << (char)(solution[i][j] + 64) << " ";
			}
			out << std::endl;
		}
	}
	else
		std::cout << "There's no solution" << std::endl;

	in.close();
	out.close();
	return 0;
}