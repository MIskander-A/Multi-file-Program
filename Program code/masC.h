#pragma once
#ifndef _masC_
#define _masC_
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

#include  "masB.h"
#include  "structTypes.h"
#include  "exception.h"
using namespace std;

class masC : public masB
{
protected:
	Record* pz;
	int l;
public:
	// Специальные методы класса
	masC() :pz(NULL), l(0) {};
	masC(masC& z);
	//  Виртуальный детруктор
	virtual ~masC() { if (pz != NULL) delete[]pz; cout << "~masC() \n"; }
	masC& operator=(masC& z);
	//  Перегруженная виртуальная операция присваивания
	virtual masC& operator=(masA& z);

	//Методы только masC
	void findGrup();
	//Переопределяемые методы

	void sort1();
	//Виртуальные методы
	virtual void output();
	virtual void outputFile();
	virtual void sort2();

	//friend ostream& operator<<(ostream& out, masC& z);
};
#include "masC.cpp"
#endif