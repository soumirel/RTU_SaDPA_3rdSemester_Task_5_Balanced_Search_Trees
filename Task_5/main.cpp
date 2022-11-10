
#include <iostream>
#include <locale.h>
#include <random>
#include "BinaryFile.h"
#include "BinarySearchTree.h"
#include "AVL-B-Tree.h"

using namespace std;

enum MenuState
{
	INIT = 0,
	EXIT = 7
};

void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//Переменные для пользовательского выбора.
	int userMenuChoice = -1;

	//Переменные для работы программы
	BinaryFile* file;

	// Главный меню-цикл.
	while (userMenuChoice != 7)
	{
		std::system("cls");
		cout << "Практическая работа #4 ИКБО-03-21 Мазанов А.Е. Вариант 15\n\n"
			"Задание - Деревья.\n"
			"~~~~~~~~~~~~~~~~~Меню~~~~~~~~~~~~~~~\n";

		cout << "Введите [0] - ТЕСТ Бинарное дерево поиска"
				"Введите [1] - ТЕСТ Сбалансированное дерево поиска"
			"\nВведите [7], чтобы закончить работу программы."
			"\nВаш выбор: ";
		
		cin >> userMenuChoice;
		cin.ignore();
		
		switch (userMenuChoice)
		{
		case 0:
		{
			string fileName = "fileName";
			file = new BinaryFile(fileName);
			cout << "Содержимое файла\n";
			file->print();
			cout << "-------------------\n";
			BinaryTreeManager tree(file);
			cout << "Дерево:\n";
			tree.print();
			cout << "-------------------\n";
			cout << "Удаление элемента 23.04\n";
			char key[6] = "23.04";
			tree.remove(key);
			cout << "Дерево:\n";
			tree.print();
			cout << "-------------------\n";
			cout << "Поиск элемента 12.02\n";
			strcpy_s(key, "12.02");
			cout << "Прямым доступом\n";
			cout << tree.find(key) << endl;
			cout << "Линейным поиском\n";
			cout << file->find(key) << '\n';
			break;
		}

		case 1:
		{
			string fileName = "fileName";
			file = new BinaryFile(fileName);
			cout << "Содержимое файла";
			file->print();
			cout << "-------------------\n";
			BTreeManager tree(file, 3);
			cout << "Дерево\n";
			tree.print();
			cout << "-------------------\n";
			cout << "Удаление элемента 23.04\n";
			char key[6] = "23.04";
			tree.remove(key);
			cout << "Дерево:\n";
			tree.print();
			cout << "-------------------\n";
			cout << "Поиск элемента 12.02\n";
			strcpy_s(key, "12.02");
			cout << "Прямым доступом\n";
			cout << tree.find(key) << endl;
			cout << "Линейным поиском\n";
			cout << file->find(key) << '\n';
			break;
			break;
		}

		case 7:
			cout << "\nДо свидания!\n";
			break;

		default:
			cout << "\nЯ не понимаю вас.\n";
			cin.clear();
			break;
		}
		std::system("pause");
	}
}