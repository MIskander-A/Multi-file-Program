#pragma once
#ifndef _masB_
#define _masB_
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

class masB : public masA
{
protected:
atr* py;
int k;
public:
masB() :py(NULL), k(0) {};
masB(masB& z);
virtual ~masB() { if (py != NULL) delete[]py; cout << "~masB()\n"; }
masB& operator=(masB& z);
virtual masB& operator= (masA& z);

//Переопределяемые методы класса 

void sort1();
//Методы только в masB
void makePerech();
//Виртуальные методы
virtual void output();
virtual void outputFile();
virtual void sort2();

};
#include "masB.cpp"
#endif
