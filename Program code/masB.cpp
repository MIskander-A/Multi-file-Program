#include  "masB.h"
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
using namespace std;



masB::masB(masB& z)
try : masA(z)
{
	int i;
	k = z.k;
	if (z.py == NULL) py = NULL;
	else {
		try { py = new atr[k];
		//throw bad_alloc(); 
		}
		catch (bad_alloc)
		{
			py = NULL; k = 0;
			throw ErrMem("��� ������", "������� (py)",
				"masB(masB &z)");
		}
		if (py == NULL) {
			cout << "��� ������.\n";
			cout << "����������� �����������.\n";
			system("pause"); exit(1);
		}
		for (i = 0; i < k; i++)
			py[i] = z.py[i];
	}
}
catch (ErrMem & ex) {
	throw ErrMem(ex.getMes(), ex.getMes1(),
		"masB(masB &z)");
}

masB& masB:: operator = (masB& z)//����������� ������������� �������� ������������ ������ masA
{
	int i;
	if (this == &z) return *this;

	// ����� ������������� �������� ������������ ������ mas� ��� 
	masA :: operator=(z);  // ������������ ������������ ����� ������� z
	if (py != NULL) delete[] py;
	k = z.k;
	if (z.py == NULL) py = NULL;
	else {
		try { py = new atr[k];
		/*throw bad_alloc();*/
		}
		catch (bad_alloc)
		{
			py = NULL; k = 0;
			throw ErrMem("��� ������", "������� (py)",
				"masB::operator=(masB &z))");
		}
		if (py == NULL) {
			cout << "��� ������ ��� ������������. \n";
			system("pause"); return z;
		}
		for (i = 0; i < k; i++)
			py[i] = z.py[i];
	}
	return *this;
}

masB& masB:: operator = (masA& z)//������������� �������� �����������
{
	int i;
	masB  r;
	if (this == &z) return *this;

	// ����� ������������� �������� ������������ ������ mas� ��� 
	masA :: operator=(z);  // ������������ ������������ ����� ������� z
	r = (masB&)z;
	if (py != NULL) delete[] py;
	k = r.k;
	if (r.py == NULL) py = NULL;
	else {
		try {
			py = new atr[k];
			//throw bad_alloc();
		}
		catch (bad_alloc)
		{
			throw ErrMem("��� ������", "������� (py)",
				"masB::operator=(masB &z))");
		}
		for (i = 0; i < k; i++)
			py[i] = r.py[i];
	}
	return *this;
}

//void makePerech();

void masB::sort1()
{
	atr tmp;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (py[i].attributes < py[j].attributes)
			{
				tmp = py[i];
				py[i] = py[j];
				py[j] = tmp;
			}
		}
	}

	//while (fl == 1); 
	//cout << "�������� ��������� � ��������� ����� ������(��������� ������������ �� ���������). \n";
	system("pause");
}

void masB::makePerech()
{
	int i, j, fl;
	atr* y;
	try {
		y = new atr[n];
		/*throw bad_alloc(); */

	}
	catch (bad_alloc)                               //  ���������� ��� �������� ������
	{
		throw ErrMem("��� ������", "�������� ������� (�������)",
			"makePerech()");
	}

	//n = v.n;
	//y = new atr[n];
	if (y == NULL)
	{
		cout << "��� ������.\n";
		_getch();
		return;
	}
	k = 0;
	if (py != NULL) delete[] py;
	py == NULL;

	for (i = 0; i < n; i++)
	{
		fl = 0;
		for (j = 0; j < k; j++)
			if (px[i].attributes == y[j].attributes)
			{
				fl = 1; y[j].count++;
			}

		if (fl == 0)
		{
			y[k].attributes = px[i].attributes;
			y[k].count = 1;
			k++;
		}
	}

	try {
		py = new atr[k];
		//throw bad_alloc();
	}
	catch (bad_alloc)                               //  ���������� ��� �������� ������
	{
		py == NULL;
		k = 0;
		delete[] y;
		throw ErrMem("��� ������", " �������(py)", "makePerech()");
	}


	//py = new atr[k];
	//if (py == NULL) {
	//	cout << "��� ������ ��� �������.\n";
	//	system("pause"); k = 0; delete[] y; return;
	//}
	////w.k = k;
	for (j = 0; j < k; j++)
		py[j] = y[j];
	delete[] y;
	cout << "�������� �����������.\n";
	system("pause");

}

//void sortDat();
//void sortChis();
void masB::sort2()
{
	atr tmp;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (py[i].count < py[j].count)
			{
				tmp = py[i];
				py[i] = py[j];
				py[j] = tmp;
			}
		}
	}

	//cout << "�������� ��������� � ��������� �� �����(��������� ������������ �� ���������). \n";
	system("pause");
}
void masB::output()
{
	cout << "��������" << endl;
	cout << "|---|-------------|------------ |" << endl;
	cout << "| � |  �������    |   ���-��    |" << endl;
	cout << "|---|-------------|-------------|" << endl;
	for (int i = 0; i < k; i++)
	{
		//cout << py[i];
		cout << "|" << std::setw(3) << i + 1 << "|" << std::setw(13) << py[i].attributes << "|" << setw(13) << py[i].count << "|" << endl;
	}
	cout << "|-------------------------------|" << endl;
	system("pause");
}

void masB::outputFile()
{
	ofstream fout;

	string file;

	int i;

	cout << "��� ��������� �����:";
	cin >> file;

	fout.open(file.c_str());

	// ������ �� ������������� ����� ����� �����

	if (fout.fail()) if (fout.fail()) throw ErrFile("�� ��������� ����", file,
		"mas�::outputFile");
	//{
	//	cout << file << "�� ���������.\n";
	//	system("pause"); return;
	//	
	//}

	// ����� ���������

	fout << "��������" << endl;
	fout << "|---|-------------|------------ |" << endl;
	fout << "| � |  �������    |   ���-��    |" << endl;
	fout << "|---|-------------|-------------|" << endl;
	fout << left;
	for (int i = 0; i < k; i++)
	{
		//cout << py[i];
		fout << "|" << std::setw(3) << i + 1 << "|" << std::setw(13) << py[i].attributes << "|" << setw(13) << py[i].count << "|" << endl;
	}
	fout << "|-------------------------------|" << endl;
	cout << "������ �������� �������� � ����\n";
	fout.close();
	system("pause");


}
