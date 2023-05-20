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

//��������� �������, ������������ �������� ����������� �������
void print(masA& z);
void printFile(masA* p);

//����������� �������, ������������ �������� ����������� �������
void print(masA& z)
{
	z.output();
}
void printFile(masA* p)
{
	p->outputFile();
}

void printA(masC* p);  //  ����� 1-� �������
void printB(masC* p);
void printC(masC* p);

void printA(masC* p)                     //  ����� 1-� �������
{
	p->masA::output();
}

void printB(masC* p)               //  ����� 2-� �������
{
	p->masB::output();
}

void printC(masC* p)                //  ����� 3-� �������
{
	p->masC::output();
}


void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
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
		cout << "������: ��� ������ ��� ��������\n";
		system("pause"); return(0);
	}

	//ifstream fin;
	//ofstream fout;

	while (1)
	{
		try {
			system("cls");
			cout << "1. ���� ������ �� �����\n";
			cout << "2. ����� �� ����� ������ � ����������� ���������\n";
			cout << "3. ���������� ����������� ��������� � ����\n";
			cout << "4. ���������� ������\n";
			cout << "5. �������� ������\n";
			cout << "6. ���������� �� ��������, � ������ �������� �� ����� ����� � ����������\n";
			cout << "7. ���������� ���������� �� ��������, ����� ����� � ����������\n";
			cout << "8. �������� ���������� �� ���� � ������� ��������\n";
			cout << "9. ������������ �������� ���������. \n";
			cout << "10. ����� ������� �� �����.\n";
			cout << "11. ����� ������� � ����.\n";
			cout << "12. ���������� ������� �� �������� .\n";
			cout << "13. ���������� ������� �� ���-�� ������ .\n";
			cout << "14. ����� �� ���� � �������. \n";
			cout << "15. ����� �� ����� ���������� ������. \n";
			cout << "16. ���������� � ���� ���������� ������. \n";
			cout << "17. ���������� ���������� ������ �� ��������, ����� ����� � ����������. \n";
			cout << "18. ���������� ���������� ������ �� ��������. \n";
			cout << "19. �������� ������������ ����������� ��� masC.\n";
			cout << "20. �������� ������-� �������� ������������ ��� masC\n";
			cout << "21. �������� ����������� �������� ������������ \n";
			cout << "22. ����� �� ���������.\n";

			cout << "��� ����� (1-22): ";

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
					throw Err("��� �� ����� ����", "main()");
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
			//	cout << "��� �� ����� ����\n";
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
			case 9: ((masB*)pa)->makePerech(); break;
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


			case 22: cout << "����� ������\n";
				delete pa;
				delete pb;
				delete pc;
				system("pause"); return;
			default: throw Err("��� ������ ������ � ���� ", "main()");
			}                                                                    //   ����� switch()
			}                                                                     //  ����� �������� ����� try
			catch (Err & ex) { ex.ErrOutput(); }           //  1-� ���������� �������� try
			catch (...)                                                        //  2-� ���������� �������� try
			{
				cout << "����������������� ����������\n"; _getch();
			}

		} // ����� while()
	} // ����� main()

