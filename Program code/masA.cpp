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
		catch (bad_alloc)   //   ���������� ��� �������� ������
		{
			px = NULL; n = 0;
			throw ErrMem("��� ������", "���. ������� (px)", "����������� ����������� ������ masA");
		}
		if (n == NULL) {
			cout << "��� ������.\n";
			cout << "����������� �����������.\n";
			system("pause"); exit(1);
		}

		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
}


masA& masA:: operator = (masA& z)//����������� ������������� �������� ������������ ������ masA
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
		catch (bad_alloc)   //   ���������� ��� �������� ������
		{
			px = NULL; n = 0;
			throw ErrMem("��� ������", "���. ������� (px)", "masA::operator=(masA &z)");
		}
		if (px == NULL) {
			cout << "��� ������!\n";
			cout << "�������� ������������\n";
			system("pause");
			return z;
		}
		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
	return *this;
}

	//������ ��� ������ masA
void masA::inputFile()
{
	ifstream fin;
	string fil;
	Record t;
	cout << "��� �������� �����: ";
	cin >> fil;
	fin.open(fil.c_str());

	//if (fin.fail())
	//{
	//	cout << fil << "  �� �����������\n";
	//	system("pause"); return;
	//}
	if (fin.fail())
		throw ErrFile("�� �����������", fil, "inputFile()");
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

	catch (bad_alloc)                     //   ���������� ��� �������� ������
	{
		px = NULL; n = 0;
		throw ErrMem("��� ������", "���. ������� (px)", "inputFile()");
	}



	//fin.open(fil.c_str());

	//if (fin.fail())
	//{
	//	cout << fil << "�������� �� �����������\n";
	//	system("pause"); n = 0; return;
	//}

	//px = new Record[n];

	if (px == NULL)
	{
		cout << "��� ������\n"; fin.close();
		cout << "������ �� �������\n";
		system("pause"); n = 0; return;
	}

	for (int i = 0; i < n; i++)
	{
		fin >> px[i].file.catalog >> px[i].file.filename >> px[i].file.extension >> px[i].date.d >> px[i].date.m >> px[i].date.y
			>> px[i].time.h >> px[i].time.m >> px[i].attributes;
	}

	fin.close();
	cout << "���� ������\n";
	system("pause");
}

void masA::addRecord()
{
	int i;
	Record t, * p;
	try {      //   ������   try - �����
		p = new Record[n + 1];  // ��������� ������ ��� ������ �������
		/*throw bad_alloc();*/
	}
	catch (bad_alloc)     //   ���������� ��� �������� ������
	{
		p = NULL; n = 0;
		throw ErrMem("��� ������", "���. ������� (p)", "adddan()");
	}
	if (p == NULL) {
		cout << "��� ������.\n";
		cout << "�������� �� �������.\n";
		system("pause"); return;
	}

	try {

		//p = new Record[n + 1]; //��������� ������ ��� ������ �������

		cout << "catalog: ";
		cin >> t.file.catalog;
		if (cin.fail())
		{
			throw Err("��� �����", "catalog");
		}
		cout << "filename: ";
		cin >> t.file.filename;
		if (cin.fail())
		{
			throw Err("��� �����", "filename");
		}
		cout << t.file.filename << endl;
		cout << "extension: ";
		cin >> t.file.extension;
		if (cin.fail())
		{
			throw Err("��� �����", "extension");
		}
		cout << "date: ";
		cin >> t.date.d;
		cin >> t.date.m;
		cin >> t.date.y;
		if (cin.fail())
		{
			throw Err("��� �����", "date");
		}
		cout << "time: ";
		cin >> t.time.h;
		cin >> t.time.m;
		if (cin.fail())
		{
			throw Err("��� �����", "time");
		}
		//cin.clear();
		cout << "attribute: ";
		//cin.ignore();
		cin >> t.attributes;
		if (cin.fail())
		{
			throw Err("��� �����", "attribute");
		}

		for (i = 0; i < n; i++) { p[i] = px[i]; } //����������� ������� ������� � �����
		p[n] = t; //���������� ����� ������ � ������ ��������
		n++;   //���������� �������� ���-�� �������

		if (px != NULL)
		{
			delete[] px;
		}
		px = p; // ����� ������ ������� ��������� � px

		cout << "������ ���������\n";
		system("pause");
	}
	catch (bad_alloc)                     //   ���������� ��� �������� ������
	{
		throw ErrMem("��� ������", "��� �������", "addStudent()");
	}

}

void masA::deleteRecord()
{
	int i, j;
	Record* p;
	//Record* p = NULL;
	char ch;
	masA::output(); //����� �� ����� ������� ��������
	cout << "����� �������� �������: ";
	//cin >> j;

	try {
		cin >> j;                                //    ��������� ���� try 
		if (cin.fail()) { throw Err("��� �� ����� ������", "deleteStudent()"); }
		//      ��������� ���������� (3)
	}
	catch (Err ex[])                           //  ���������� ��� �������� ������
	{
		//cin.clear();
		/*do { cin >> ch; } while (ch == '\n');
		throw; */                                   //    ��������� ��������� ���������� (3)
		throw Err("��� �� ����� ������", "deleteStudent()");
	}



	//if (cin.fail())
	//{
	//	string s;
	//	cin.clear();
	//	cin >> s;
	//	cout << "��� �� ����� ������\n";
	//	cout << "�������� �� ���������\n";
	//	system("pause");
	//	return;
	//}

	if (j < 1 || j > n)
		throw Err("��� ����� ������", "deleteStudent()");
	//{
	//	cout << "��� ����� ������\n";
	//	cout << "�������� �� ���������\n";
	//	system("pause"); return;
	//}

	j--;
	cout << j + 1 << "-� ������:\n";
	cout << " " << px[j].file.catalog << "." << px[j].file.filename << "." << px[j].file.extension << " " << px[j].date.d << " " << px[j].date.m << " " << px[j].date.y << " " << px[j].time.h << " " << px[j].time.m << " " << px[j].attributes << endl;
	cout << "�������? (y/n):"; cin >> ch;

	if (char(cin.peek()) != '\n')
	{
		cin.ignore();
		cin.clear();
		cin.ignore(32767, '\n');
	}

	if (ch == 'n') throw Err("��� �� �� ������", "deleteStudent()");
	//{
	//	cout << "�� ��� ������\n"; system("pause"); return;
	//}
	if (ch != 'y') throw Err("����� �� �� �� ��� ", "deleteStudent()"); //{ cout << "������: ����� �� ������������� ��/���\n"; system("pause"); return; }

	if (n == 1) { delete[] px; px = NULL; n = 0; }
	else
	{
		try {
			p = new Record[n - 1];
			/*throw bad_alloc(); */
		}
		catch (bad_alloc)               //  ���������� ��� �������� ������
		{
			throw ErrMem("��� ������", "���. ������� (px)", "deleteStudent()");
		}

		if (p == NULL)
		{
			cout << "��� ������\n ";
			cout << "������� �� �������\n";
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

	cout << "������ �������\n";
	system("pause");
}



//��������� m����� ������
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

//����������� m����� ������
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
	cout << "��� ��������� �����: "; cin >> fil;
	fout.open(fil.c_str());

	if (fout.fail()) throw ErrFile("�� ��������� ����", fil, "masA::outputFile");
	//{
	//	cout << fil << "�� ���������\n";
	//	system("pause"); return;
	//}

	fout << "-------------------------------------------------------------------------------------------------\n";
	fout << "|   |                      |                       |            |            |       |           |\n";
	fout << "| � |       �������        |       ��� �����       | ���������� |    ����    | ����� |  �������  |\n";
	fout << "|   |                      |                       |            |            |       |           |\n";
	fout << "-------------------------------------------------------------------------------------------------\n";

	for (i = 0; i < n; i++)
		fout << "|" << std::setw(3) << std::left << i + 1 << "|" << std::setw(22) << std::left << px[i].file.catalog << "|" << std::setw(23) << std::left << px[i].file.filename << "|" << std::setw(12) << std::left << px[i].file.extension << "|" << std::setw(2)
		<< px[i].date.d << std::setw(1) << "." << std::setw(2) << px[i].date.m << std::setw(1) << "." << std::setw(6) << px[i].date.y << "|" << std::setw(3) << std::right
		<< px[i].time.h << ":" << std::setw(3) << std::left << px[i].time.m << "|" << std::setw(11) << std::left << px[i].attributes << "|" << endl;
	fout << "------------------------------------------------------------------------------------------------\n";
	fout.close();
	cout << "������ �������� �������� � ����\n";
	system("pause");
}
void masA::output()
{
	int i;
	cout << "-------------------------------------------------------------------------------------------------\n";
	cout << "|   |                      |                       |            |            |       |           |\n";
	cout << "| � |       �������        |      ��� �����        | ���������� |    ����    | ����� |  �������  |\n";
	cout << "|   |                      |                       |            |            |       |           |\n";
	cout << "-------------------------------------------------------------------------------------------------\n";
	//cout << left;
	for (int i = 0; i < n; i++)
	{

		//cout << "|" << std::setw(2) << i + 1 << px[i]<< endl; //�out<<px[i]  ��� ������������� �������� ������ �� ����� 

		cout << "|" << std::setw(3) << std::left << i + 1 << "|" << std::setw(22) << std::left << px[i].file.catalog << "|" << std::setw(23) << std::left << px[i].file.filename << "|" << std::setw(12) << std::left << px[i].file.extension << "|" << std::setw(2)
			<< px[i].date.d << std::setw(1) << "." << std::setw(2) << px[i].date.m << std::setw(1) << "." << std::setw(6) << px[i].date.y << "|" << std::setw(3) << std::right
			<< px[i].time.h << ":" << std::setw(3) << std::left << px[i].time.m << "|" << std::setw(11) << std::left << px[i].attributes << "|\n";
	}
	cout << "------------------------------------------------------------------------------------------------\n";
	system("pause");
}

