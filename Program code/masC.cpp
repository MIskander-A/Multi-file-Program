#include  "masC.h"
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
using namespace std;


masC::masC(masC& z)
try : masB(z)
{
	int i;
	l = z.l;
	if (z.pz == NULL) pz = NULL;
	else {
		try { pz = new Record[l]; 
		//throw bad_alloc();
		}
		catch (bad_alloc)
		{
			pz = NULL; l = 0;
			throw ErrMem("��� ������", " ���. ������� (pz)",
				" masC (masC &z)");
		}
		for (i = 0; i < k; i++)
			pz[i] = z.pz[i];

	}
}
catch (ErrMem & ex) {
	throw ErrMem(ex.getMes(), ex.getMes1(),
		"masC(masC &z)");
}


masC& masC::operator = (masC& z)//����������� ������������� �������� ������������ ������ masA
{
	int i;
	if (this == &z) return *this;

	// ����� ������������� �������� ������������ ������ mas� ��� 
	masB :: operator=(z);  // ������������ ������������ ����� ������� z

	if (pz != NULL) delete[] pz;
	l = z.l;
	if (z.pz == NULL) pz = NULL;
	else {
		try { pz = new Record[l];
		//throw bad_alloc(); 
		}
		catch (bad_alloc)
		{
			pz = NULL; l = 0;
			throw ErrMem("��� ������", "���. ������� (pz)",
				" masC::operator=( masC &z)");
		}
		if (pz == NULL)
		{
			cout << "��� ������ ��� ������������!\n";
			system("pause"); return z;
		}
		for (i = 0; i < k; i++)
			pz[i] = z.pz[i];
	}
	return *this;
}

masC& masC::operator = (masA& z)//������������� �������� ����������� 
{
	int i;
	masC  r;
	if (this == &z) return *this;

	// ����� ������������� �������� ������������ ������ mas� ��� 
	masB :: operator=(z);  // ������������ ������������ ����� ������� z
	r = (masC&)z;
	if (pz != NULL) delete[] pz;
	l = r.l;
	if (r.pz == NULL) pz = NULL;
	else {
		try { pz = new Record[l];
		//throw bad_alloc();
		}
		catch (bad_alloc)
		{

			throw ErrMem("��� ������", "���. ������� (pz)",
				" masC::operator=( masC &z)");
		}
		for (i = 0; i < k; i++)
			pz[i] = r.pz[i];
	}
	return *this;
}
void masC::sort1()
{
	Record tmp;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (pz[i].file.catalog < pz[j].file.catalog)
			{
				tmp = pz[i];
				pz[i] = pz[j];
				pz[j] = tmp;
			}
		}
	}
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (pz[i].file.catalog == pz[j].file.catalog && pz[i].file.filename < pz[j].file.filename)
			{
				tmp = pz[i];
				pz[i] = pz[j];
				pz[j] = tmp;
			}
		}
	}
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (pz[i].file.catalog == pz[j].file.catalog && pz[i].file.filename == pz[j].file.filename && pz[i].file.extension < pz[j].file.extension)
			{
				tmp = pz[i];
				pz[i] = pz[j];
				pz[j] = tmp;
			}
		}
	}
	system("pause");
}
void masC::findGrup()
{
	int i, j;
	Date tmpD;
	Time tmpT;
	Record* y;
	try {
		y = new Record[n];
		/*throw bad_alloc();*/
	}
	catch (bad_alloc)                           //  ���������� ��� �������� ������
	{
		throw ErrMem("��� ������", "���. ������� (y)", "findGrup()");
	}

	/*y = new Record[n];
	if (y == NULL)
	{
		cout << "��� ������.\n";
		system("pause"); return;
	}*/
	cout << "������� ����: ";
	cin >> tmpD.d >> tmpD.m >> tmpD.y;
	if (cin.fail())
	{
		throw Err("��� �����", "����");
	}
	cout << "������� �����: ";
	cin >> tmpT.h >> tmpT.m;
	if (cin.fail())
	{
		throw Err("��� �����", "�������");
	}
	l = 0;
	for (i = 0; i < n; i++)
		if (px[i].date == tmpD && px[i].time == tmpT)
		{
			y[l] = px[i];
			l++;
		}
	if (pz != NULL) {
		delete[] pz; return;
	}
	try {
		pz = new Record[l];
		/*throw bad_alloc();*/
	}
	catch (bad_alloc)                            //  ���������� ��� �������� ������
	{
		pz = NULL;
		l = 0;
		delete[]y;
		throw ErrMem("��� ������", "������� ����. (pz)", "findGrup()");
	}

	//pz = new Record[l];
	//if (pz == NULL)
	//{
	//	cout << "��� ������\n";
	//	system("pause");
	//	l = 0;
	//	delete[] y;
	//	return;
	//}
	for (j = 0; j < l; j++)
		pz[j] = y[j];
	delete[] y;
	cout << "������ �� ���� � ������� �����������. \n";
	system("pause");

}


void masC::sort2()
{
	Record tmp;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (pz[i].attributes < pz[j].attributes)
			{
				tmp = pz[i];
				pz[i] = pz[j];
				pz[j] = tmp;
			}
		}
	}

	//while (fl == 1);
	//cout << "������ ������ �� �������� ��������������� �� ���� � ������� ��������\n";
	system("pause");
}
void masC::output()
{
	
	cout << "�����" << endl;
	cout << "-------------------------------------------------------------------------------------------------\n" << endl;
	cout << "|   |                      |                       |            |            |       |           |\n" << endl;
	cout << "| � |       �������        |      ��� �����        | ���������� |    ����    | ����� |  �������  |\n" << endl;
	cout << "|   |                      |                       |            |            |       |           |\n" << endl;
	cout << "-------------------------------------------------------------------------------------------------\n" << endl;
	for (int i = 0; i < l; i++)
	{
		/*cout << "|" <<setw(2) << left << i + 1 << pz[i] << endl;*/
		cout << "|" << std::setw(3) << std::left << i + 1 << "|" << std::setw(22) << std::left << pz[i].file.catalog << "|" << std::setw(23) << std::left << pz[i].file.filename << "|" << std::setw(12) << std::left << pz[i].file.extension << "|" << std::setw(2)
			<< pz[i].date.d << std::setw(1) << "." << std::setw(2) << pz[i].date.m << std::setw(1) << "." << std::setw(6) << pz[i].date.y << "|" << std::setw(3) << std::right
			<< pz[i].time.h << ":" << std::setw(3) << std::left << pz[i].time.m << "|" << std::setw(11) << std::left << pz[i].attributes << "|\n";
	}
	cout << "-------------------------------------------------------------------------------------------------\n" << endl;
	system("pause");
}
void masC::outputFile()
{
	ofstream fout;

	string file;

	int i;

	cout << "��� ��������� �����:";
	cin >> file;

	fout.open(file.c_str());

	// ������ �� ������������� ����� ����� �����

	if (fout.fail())  if (fout.fail()) throw ErrFile("�� ��������� ����", file,
		"mas�::outputFile");
	//{
	//	cout << file << "�� ���������\n";
	//	system("pause"); return;
	//}

	// ����� ���������
	fout << "�����" << endl;
	fout << "--------------------------------------------------------------------------------------------------\n";
	fout << "|   |                      |                       |            |            |       |           |\n";
	fout << "| � |       �������        |       ��� �����       | ���������� |    ����    | ����� |  �������  |\n";
	fout << "|   |                      |                       |            |            |       |           |\n";
	fout << "--------------------------------------------------------------------------------------------------\n";

	// ����� ��������� ����� �������

	for (i = 0; i < l; i++)

		fout << "|" << std::setw(3) << std::left << i + 1 << "|" << std::setw(22) << std::left << pz[i].file.catalog << "|" << std::setw(23) << std::left << pz[i].file.filename << "|" << std::setw(12) << std::left << pz[i].file.extension << "|" << std::setw(2) << pz[i].date.d << std::setw(1) << "." << std::setw(2) << pz[i].date.m << std::setw(1) << "." << std::setw(6) << pz[i].date.y << "|" << std::setw(3) << std::right << pz[i].time.h << ":" << std::setw(3) << std::left << pz[i].time.m << "|" << std::setw(11) << std::left << pz[i].attributes << "|" << endl;

	fout << "-------------------------------------------------------------------------------------------------\n";

	fout.close();

	cout << "������ �������� �������� � ����\n";
	system("pause");
}


