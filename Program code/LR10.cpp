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
#include  "masA.h"
#include  "masB.h"
#include  "masC.h"
using namespace std;

//Прототипы функций, использующих механизм виртуальных функций
void print(masA& z);
void printFile(masA* p);

//Определение функций, использующих механизм виртуальных функций
void print(masA& z)
{
	z.output();
}
void printFile(masA* p)
{
	p->outputFile();
}

void printA(masC* p);  //  Вывод 1-й таблицы
void printB(masC* p);
void printC(masC* p);

void printA(masC* p)                     //  Вывод 1-й таблицы
{
	p->masA::output();
}

void printB(masC* p)               //  Вывод 2-й таблицы
{
	p->masB::output();
}

void printC(masC* p)                //  Вывод 3-й таблицы
{
	p->masC::output();
}


void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	//masC c;
	int j;
	char ch;
	masA* pa, * pb, * pc;
	masC* pd;
	try {
		pa = pd = new masC;
		pb = new masC;
		pc = new masC;
	}
	catch (bad_alloc)
	{
		cout << "Ошибка: нет памяти для объектов\n";
		system("pause"); return;
	}

	//ifstream fin;
	//ofstream fout;

	while (1)
	{
		try {
			system("cls");
			cout << "1. Ввод данных из файла\n";
			cout << "2. Вывод на экран данных и результатов обработки\n";
			cout << "3. Сохранение результатов обработки в файл\n";
			cout << "4. Добавление записи\n";
			cout << "5. Удаление записи\n";
			cout << "6. Сортировка по атрибуту, а внутри атрибута по имени файла и расширению\n";
			cout << "7. Алфавитная сортировка по каталогу, имени файла и расширению\n";
			cout << "8. Числовая сортировка по дате и времени создания\n";
			cout << "9. Формирование переченя атрибутов. \n";
			cout << "10. Вывод перечня на экран.\n";
			cout << "11. Вывод перечня в файл.\n";
			cout << "12. Сортировка перечня по атрибуту .\n";
			cout << "13. Сортировка перечня по кол-ву файлов .\n";
			cout << "14. Поиск по дате и времени. \n";
			cout << "15. Вывод на экран результата поиска. \n";
			cout << "16. Сохранение в файл результата поиска. \n";
			cout << "17. Сортировка результата поиска по каталогу, имени файла и расширению. \n";
			cout << "18. Сортировка результата поиска по атрибуту. \n";
			cout << "19. Проверка конструктора копирования для masC.\n";
			cout << "20. Проверка перегр-й операции присваивания для masC\n";
			cout << "21. Проверка виртуальной операции присваивания \n";
			cout << "22. Выход из программы.\n";

			cout << "Ваш выбор (1-22): ";

			try
			{
				if (char(cin.peek()) == '\n')
					cin.ignore();

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
				}
				cin >> j;
				if (cin.fail())
				{
					throw Err("Это не пункт меню", "main()");
				}
			}
			catch (Err & ex)
			{
				throw;
			}







			//if (cin.fail())
			//{
			//	string s;
			//	cin.clear(); 
			//	cin >> s;
			//	cout << "Это не пункт меню\n";
			//	system("pause");
			//	continue;
			//}

			switch (j)
			{
			case 1: pa->inputFile(); break;
			case 2: pa->masA::output(); break;
			case 3: pa->masA::outputFile(); break;
			case 4: pa->addRecord(); break;
			case 5: pa->deleteRecord(); break;
			case 6: pa->masA::sort1(); break;
			case 7: pa->masA::sort2(); break;
			case 8: pa->masA::sort3(); break;
			case 9: ((masB*)pa)->masB::makePerech(); break;
			case 10: ((masB*)pa)->masB::output(); break;
			case 11: {((masB*)pa)->masB::outputFile(); break;
			case 12: ((masB*)pa)->masB::sort1(); break;
			case 13: ((masB*)pa)->masB::sort2(); break;
			case 14: ((masC*)pa)->findGrup(); break;
			case 15: pa->output(); break;
			case 16: pa->outputFile(); break;
			case 17: ((masC*)pa)->sort1(); break;
			case 18: ((masC*)pa)->sort2(); break;
			case 19: {masC c(*pd);
				printA(pd); printA(&c);
				printB(pd); printB(&c);
				printC(pd); printC(&c); }
				   break;


			case 20: { masC a, b;
				a = b = *pd;
				printA(pd); printA(&b); printA(&a);
				printB(pd); printB(&b); printB(&a);
				printC(pd); printC(&b); printC(&a); } break;


			case 21: { masC* pb2, * pc2;
				*pc = *pb = *pa;
				pb2 = (masC*)pb;
				pc2 = (masC*)pc;
				printA(pd); printA(pb2); printA(pc2);
				printB(pd); printB(pb2); printB(pc2);
				printC(pd); printC(pb2); printC(pc2);
			}  break;


			case 22: cout << "Конец работы\n";
				delete pa;
				delete pb;
				delete pc;
				system("pause"); return;
			default: throw Err("Нет такого пункта в меню ", "main()");
			}                                                                    //   конец switch()
			}
		}//  конец внешнего блока try
		catch (Err & ex) { ex.ErrOutput(); }           //  1-й обработчик внешнего try
		catch (...)                                                        //  2-й обработчик внешнего try
		{
			cout << "Непредусмотренное исключение\n"; _getch();
		}

	} // конец while()
} // конец main()
