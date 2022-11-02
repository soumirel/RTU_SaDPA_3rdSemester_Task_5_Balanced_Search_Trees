
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
			file->print();
			cout << "-------------------\n";
			BinarySearchTree tree(file);
			tree.print();
			cout << "-------------------\n";
			char key[6] = "23.04";
			tree.remove(key);
			tree.print();
			break;
		}

		case 1:
		{
			string fileName = "fileName";
			file = new BinaryFile(fileName);
			file->print();
			cout << "-------------------\n";
			BTree t(3);
			t.insert("11.11");
			t.insert("10.06");
			t.insert("31.02");
			t.insert("14.03");
			t.insert("12.11");
			t.insert("11.06");
			t.insert("30.02");
			t.insert("15.03");

			string k = "31.02";
			(t.get(k) != NULL) ? cout << endl
				<< k << " найдено"
				: cout << endl
				<< k << " не найдено";
			
			t.remove("31.02");

			(t.get(k) != NULL) ? cout << endl
				<< k << " найдено"
				: cout << endl
				<< k << " не найдено\n";

			BTreePrinter printer(&t);
			printer.print();
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