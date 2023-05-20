#include  "masa.h"
#define NOMINMAX
#include  <iostream>
#include  <limits>
#include  <fstream>
#include  <cstdlib>
#include  <string>
#include  <iomanip>
#include  <conio.h>
#include  <Windows.h>
#include  <sstream>

#include  "structTypes.h"
#include  "exception.h"
using namespace std;


masA::masA(masA& z)
{
	int i;
	n = z.n;
	if (z.px == NULL) px = NULL;
	else
	{
		try {
			px = new Record[n];
			/*throw bad_alloc();*/
		}
		catch (bad_alloc)   //   Обработчик без передачи данных
		{
			px = NULL; n = 0;
			throw ErrMem("Нет памяти", "исх. массива (px)", "Конструктор копирования класса masA");
		}
		if (n == NULL) {
			cout << "нет памяти.\n";
			cout << "Конструктор копирования.\n";
			system("pause"); exit(1);
		}

		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
}


masA& masA:: operator = (masA& z)//Определение перегруженной операции присваивания класса masA
{
	int i;
	if (this == &z) return *this;
	if (px != NULL) delete[]px;
	n = z.n;
	if (z.px == NULL) px = NULL;
	else {
		try {
			px = new Record[n];
			//throw bad_alloc();
		}
		catch (bad_alloc)   //   Обработчик без передачи данных
		{
			px = NULL; n = 0;
			throw ErrMem("Нет памяти", "исх. массива (px)", "masA::operator=(masA &z)");
		}
		if (px == NULL) {
			cout << "Нет памяти!\n";
			cout << "Операция присваивания\n";
			system("pause");
			return z;
		}
		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
	return *this;
}

	//методы для класса masA
void masA::inputFile()
{
	ifstream fin;
	string fil;
	Record t;
	cout << "Имя входного файла: ";
	cin >> fil;
	fin.open(fil.c_str());

	//if (fin.fail())
	//{
	//	cout << fil << "  не открывается\n";
	//	system("pause"); return;
	//}
	if (fin.fail())
		throw ErrFile("не открывается", fil, "inputFile()");
	n = 0;
	if (px != NULL) { delete[] px; px = NULL; }

	while (1)
	{

		fin >> t.file.catalog >> t.file.filename >> t.file.extension >> t.date.d >> t.date.m >> t.date.y
			>> t.time.h >> t.time.m >> t.attributes;
		if (fin.fail()) break; n++;
		//n++;
	}
	fin.clear();

	fin.seekg(0, ios::beg);

	try
	{
		px = new Record[n];
		/*throw bad_alloc();*/
	}

	catch (bad_alloc)                     //   Обработчик без передачи данных
	{
		px = NULL; n = 0;
		throw ErrMem("Нет памяти", "исх. массива (px)", "inputFile()");
	}



	//fin.open(fil.c_str());

	//if (fin.fail())
	//{
	//	cout << fil << "повторно не открывается\n";
	//	system("pause"); n = 0; return;
	//}

	//px = new Record[n];

	if (px == NULL)
	{
		cout << "Нет памяти\n"; fin.close();
		cout << "Ввести не удается\n";
		system("pause"); n = 0; return;
	}

	for (int i = 0; i < n; i++)
	{
		fin >> px[i].file.catalog >> px[i].file.filename >> px[i].file.extension >> px[i].date.d >> px[i].date.m >> px[i].date.y
			>> px[i].time.h >> px[i].time.m >> px[i].attributes;
	}

	fin.close();
	cout << "Файл введен\n";
	system("pause");
}

void masA::addRecord()
{
	int i;
	Record t, * p;
	try {      //   начало   try - блока
		p = new Record[n + 1];  // выделение памяти для нового массива
		/*throw bad_alloc();*/
	}
	catch (bad_alloc)     //   Обработчик без передачи данных
	{
		p = NULL; n = 0;
		throw ErrMem("Нет памяти", "исх. массива (p)", "adddan()");
	}
	if (p == NULL) {
		cout << "нет памяти.\n";
		cout << "Добавить не удается.\n";
		system("pause"); return;
	}

	try {

		//p = new Record[n + 1]; //выделение памяти для нового массива

		cout << "catalog: ";
		cin >> t.file.catalog;
		if (cin.fail())
		{
			throw Err("при вводе", "catalog");
		}
		cout << "filename: ";
		cin >> t.file.filename;
		if (cin.fail())
		{
			throw Err("при вводе", "filename");
		}
		cout << t.file.filename << endl;
		cout << "extension: ";
		cin >> t.file.extension;
		if (cin.fail())
		{
			throw Err("при вводе", "extension");
		}
		cout << "date: ";
		cin >> t.date.d;
		cin >> t.date.m;
		cin >> t.date.y;
		if (cin.fail())
		{
			throw Err("при вводе", "date");
		}
		cout << "time: ";
		cin >> t.time.h;
		cin >> t.time.m;
		if (cin.fail())
		{
			throw Err("при вводе", "time");
		}
		//cin.clear();
		cout << "attribute: ";
		//cin.ignore();
		cin >> t.attributes;
		if (cin.fail())
		{
			throw Err("при вводе", "attribute");
		}

		for (i = 0; i < n; i++) { p[i] = px[i]; } //копирование старого массива в новый
		p[n] = t; //добавление новой записи в массив структур
		n++;   //увеличение счетчика кол-ва записей

		if (px != NULL)
		{
			delete[] px;
		}
		px = p; // адрес нового массива заносится в px

		cout << "Запись добавлена\n";
		system("pause");
	}
	catch (bad_alloc)                     //   Обработчик без передачи данных
	{
		throw ErrMem("Нет памяти", "исх массива", "addStudent()");
	}

}

void masA::deleteRecord()
{
	int i, j;
	Record* p;
	//Record* p = NULL;
	char ch;
	masA::output(); //вызов на экран массива структур
	cout << "Номер удаленой стороки: ";
	//cin >> j;

	try {
		cin >> j;                                //    вложенный блок try 
		if (cin.fail()) { throw Err("Это не номер строки", "deleteStudent()"); }
		//      генерация исключения (3)
	}
	catch (Err ex[])                           //  Обработчик без передачи данных
	{
		//cin.clear();
		/*do { cin >> ch; } while (ch == '\n');
		throw; */                                   //    повторная генерация исключения (3)
		throw Err("Это не номер строки", "deleteStudent()");
	}



	//if (cin.fail())
	//{
	//	string s;
	//	cin.clear();
	//	cin >> s;
	//	cout << "Это не номер строки\n";
	//	cout << "Удаление не произошло\n";
	//	system("pause");
	//	return;
	//}

	if (j < 1 || j > n)
		throw Err("Нет такой строки", "deleteStudent()");
	//{
	//	cout << "Нет такой строки\n";
	//	cout << "Удаление не произошло\n";
	//	system("pause"); return;
	//}

	j--;
	cout << j + 1 << "-я строка:\n";
	cout << " " << px[j].file.catalog << "." << px[j].file.filename << "." << px[j].file.extension << " " << px[j].date.d << " " << px[j].date.m << " " << px[j].date.y << " " << px[j].time.h << " " << px[j].time.m << " " << px[j].attributes << endl;
	cout << "Удалить? (y/n):"; cin >> ch;

	if (char(cin.peek()) != '\n')
	{
		cin.ignore();
		cin.clear();
		cin.ignore(32767, '\n');
	}

	if (ch == 'n') throw Err("Это не та строка", "deleteStudent()");
	//{
	//	cout << "не так строка\n"; system("pause"); return;
	//}
	if (ch != 'y') throw Err("Ответ ни да ни нет ", "deleteStudent()"); //{ cout << "Ошибка: ответ не удовлетворяет да/нет\n"; system("pause"); return; }

	if (n == 1) { delete[] px; px = NULL; n = 0; }
	else
	{
		try {
			p = new Record[n - 1];
			/*throw bad_alloc(); */
		}
		catch (bad_alloc)               //  Обработчик без передачи данных
		{
			throw ErrMem("Нет памяти", "исх. массива (px)", "deleteStudent()");
		}

		if (p == NULL)
		{
			cout << "Нет памяти\n ";
			cout << "Удалить не удается\n";
			system("pause"); return;
		}
		for (i = 0; i < j; i++)
			p[i] = px[i];
		for (i = j + 1; i < n; i++)
			p[i - 1] = px[i];
		delete[] px;
		px = p;
		n--;
	}

	cout << "Запись удалена\n";
	system("pause");
}



//переопред mетоды класса
void masA::sort1()
{
	Record tmp;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (px[i].attributes < px[j].attributes)
			{
				tmp = px[i];
				px[i] = px[j];
				px[j] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (px[i].attributes == px[j].attributes && px[i].file.filename < px[j].file.filename)
			{
				tmp = px[i];
				px[i] = px[j];
				px[j] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (px[i].attributes == px[j].attributes && px[i].file.filename == px[j].file.filename && px[i].file.extension < px[j].file.extension)
			{
				tmp = px[i];
				px[i] = px[j];
				px[j] = tmp;
			}
		}
	}
	system("pause");
}

void masA::sort3()
{
	Record tmp;

	for (int i = 0; i < n; i++)
	{
		for (int g = i + 1; g < n; g++)
		{
			if (px[i].date == px[g].date)
			{
				if (px[i].time > px[g].time)
				{
					tmp = px[i];
					px[i] = px[g];
					px[g] = tmp;
				}
			}
			else if (px[i].date > px[g].date)
			{
				tmp = px[i];
				px[i] = px[g];
				px[g] = tmp;
			}

		}
	}
	system("pause");
}

//виртуальные mетоды класса
void masA::sort2()
{
	Record tmp;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (strcmp(px[i].file.catalog, px[j].file.catalog) < 0)
			{
				tmp = px[i];
				px[i] = px[j];
				px[j] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (strcmp(px[i].file.catalog, px[j].file.catalog) == 0 && strcmp(px[i].file.filename, px[j].file.filename) < 0)
			{
				tmp = px[i];
				px[i] = px[j];
				px[j] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (strcmp(px[i].file.catalog, px[j].file.catalog) == 0 && strcmp(px[i].file.filename, px[j].file.filename) == 0 && strcmp(px[i].file.extension, px[j].file.extension) < 0)
			{
				tmp = px[i];
				px[i] = px[j];
				px[j] = tmp;
			}
		}
	}
	system("pause");
}
void masA::outputFile()
{
	ofstream fout;
	string fil;
	int i;
	cout << "Имя выходного файла: "; cin >> fil;
	fout.open(fil.c_str());

	if (fout.fail()) throw ErrFile("не создается файл", fil, "masA::outputFile");
	//{
	//	cout << fil << "не создается\n";
	//	system("pause"); return;
	//}

	fout << "-------------------------------------------------------------------------------------------------\n";
	fout << "|   |                      |                       |            |            |       |           |\n";
	fout << "| № |       Каталог        |       Имя файла       | Расширение |    Дата    | Время |  Атрибут  |\n";
	fout << "|   |                      |                       |            |            |       |           |\n";
	fout << "-------------------------------------------------------------------------------------------------\n";

	for (i = 0; i < n; i++)
		fout << "|" << std::setw(3) << std::left << i + 1 << "|" << std::setw(22) << std::left << px[i].file.catalog << "|" << std::setw(23) << std::left << px[i].file.filename << "|" << std::setw(12) << std::left << px[i].file.extension << "|" << std::setw(2)
		<< px[i].date.d << std::setw(1) << "." << std::setw(2) << px[i].date.m << std::setw(1) << "." << std::setw(6) << px[i].date.y << "|" << std::setw(3) << std::right
		<< px[i].time.h << ":" << std::setw(3) << std::left << px[i].time.m << "|" << std::setw(11) << std::left << px[i].attributes << "|" << endl;
	fout << "------------------------------------------------------------------------------------------------\n";
	fout.close();
	cout << "Массив структур сохранен в файл\n";
	system("pause");
}
void masA::output()
{
	int i;
	cout << "-------------------------------------------------------------------------------------------------\n";
	cout << "|   |                      |                       |            |            |       |           |\n";
	cout << "| № |       Каталог        |      Имя файла        | Расширение |    Дата    | Время |  Атрибут  |\n";
	cout << "|   |                      |                       |            |            |       |           |\n";
	cout << "-------------------------------------------------------------------------------------------------\n";
	//cout << left;
	for (int i = 0; i < n; i++)
	{

		//cout << "|" << std::setw(2) << i + 1 << px[i]<< endl; //сout<<px[i]  это перегруженная операция вывода на экран 

		cout << "|" << std::setw(3) << std::left << i + 1 << "|" << std::setw(22) << std::left << px[i].file.catalog << "|" << std::setw(23) << std::left << px[i].file.filename << "|" << std::setw(12) << std::left << px[i].file.extension << "|" << std::setw(2)
			<< px[i].date.d << std::setw(1) << "." << std::setw(2) << px[i].date.m << std::setw(1) << "." << std::setw(6) << px[i].date.y << "|" << std::setw(3) << std::right
			<< px[i].time.h << ":" << std::setw(3) << std::left << px[i].time.m << "|" << std::setw(11) << std::left << px[i].attributes << "|\n";
	}
	cout << "------------------------------------------------------------------------------------------------\n";
	system("pause");
}

