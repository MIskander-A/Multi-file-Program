#pragma once
#ifndef _masA_
#define _masA_
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

//int operator>(dat v, dat w) //����������� ������������� �������� ��������� ��� �������� ���� dat
//{
//	if (v.y > w.y) return 1;
//	if ((v.y == w.y) && (v.m > w.m)) return 1;
//	if ((v.y == w.y) && (v.m == w.m) && (v.d > w.d)) return 1;
//	return 0;
//};


class masA
{
protected:
	Record* px;
	int n;
public:
	masA() :px(NULL), n(0) {};
	masA(masA& z);
	virtual ~masA() { if (px != NULL) delete[]px; cout << "~masA()\n"; }
	virtual masA& operator=(masA& z);

	//������ ������ � masA
	void inputFile();
	void addRecord();
	void deleteRecord();
	//���������������� ������
	void sort1();
	void sort3();
	//����������� ������
	virtual void output();
	virtual void outputFile();
	virtual void sort2();


};//����������� ������� ������ masA
#include "masA.cpp"
#endif
