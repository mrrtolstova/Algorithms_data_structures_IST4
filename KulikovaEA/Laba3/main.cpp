#include <iostream>

struct Node
{
	int field; // Поле данных
	Node * left; // Левый потомок
	Node * right; // Правый потомок
};

Node * AddNode(int x, Node * tree) 
{ // Добавление узлов в дерево
	if (tree == nullptr) 
	{ // Если дерева нет, то формируем корень
		tree = new Node(); // Память под узел
		tree->field = x; // Поле данных
		// Ветви инициализируем пустотой
		tree->left = nullptr;
		tree->right = nullptr;
	}
	else if (x < tree->field) // Условие добавление левого потомка
		tree->left = AddNode(x, tree->left);
	else // Условие добавление правого потомка
		tree->right = AddNode(x, tree->right);
	return tree;
}

void TreePrint(Node * tree) 
{// Представление дерева в префиксной форме
	if (tree != nullptr) { // Пока не встретится пустой узел
		std::cout << tree->field << " "; // Отображаем корень дерева
		TreePrint(tree->left); // Рекурсивная функция для левого поддерева
		TreePrint(tree->right); // Рекурсивная функция для правого поддерева
	}
}

Node * Task(Node * tree)
{ // Каждую вершину с четным значением поменять местами с сыном, имеющим четное значение
	if (tree != nullptr)
	{
		if (tree->field % 2 == 0)
		{ // Если в узле четное значение
			int swap = tree->field;
			if (tree->left->field % 2 == 0)
			{ // Если левый сын четный, то обмениваемся значениями
				tree->field = tree->left->field;
				tree->left->field = swap;
			}
			else if (tree->right->field % 2 == 0)
			{// Если правый сын четный, то обмениваемся значениями
				tree->field = tree->right->field;
				tree->right->field = swap;
			}
		}
		// Выполняем рекурсивно для каждого потомка
		Task(tree->left);
		Task(tree->right);
	}
	return tree;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n; // Количество значений
	std::cout << "Количество значений - ";
	std::cin >> n;
	std::cout << "Введите значения:" << std::endl;
	int x;
	Node * tree = nullptr;
	for (int i = 0; i < n; i++)
	{
		std::cin >> x;
		tree = AddNode(x, tree);
	}
	std::cout << "Бинарное дерево в префиксной форме:" << std::endl;
	TreePrint(tree);
	tree = Task(tree); // Выполнение задачи
	std::cout << std::endl << "Каждую вершину с четным значением поменять местами с сыном, имеющим четное значение:" << std::endl;
	TreePrint(tree);
	return 0;
}
