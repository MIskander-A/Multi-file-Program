#ifndef _structTypes_
#define _structTypes_
#include  <iostream>
#include  <limits>
#include  <fstream>
#include  <cstdlib>
#include  <string>
#include  <iomanip>
#include  <conio.h>
#include  <Windows.h>
#include  <sstream>
using namespace std;
class masB;
class masC; 

struct File {
	char catalog[30];
	char filename[30];
	char extension[30];
	//Date date;
};

struct Date {
	int d, m, y;
};

struct Time {
	int h, m;
};

struct Record {
	File file;
	Date date;
	Time time;
	string attributes;
	//char catalog[30];
	Date dat;
	Time tim;
};

struct atr {
	string attributes;
	int count;
};

int operator > (Date v, Date w) //Определение перегруженной операции сравнения для структур типа date

{
	if (v.y > w.y) return 1;
	if ((v.y == w.y) && (v.m > w.m)) return 1;
	if ((v.y == w.y) && (v.m == w.m) && (v.d > w.d)) return 1;
	return 0;
};
int operator > (Time v, Time w)
{
	if (v.h > w.h) return 1;
	if ((v.h == w.h) && (v.m > w.m)) return 1;
	return 0;
};

int operator == (Date v, Date w)
{
	if ((v.y == w.y) && (v.m == w.m) && (v.d == w.d)) return 1;
	return 0;
};

int operator ==(Time v, Time w)
{
	if ((v.h == w.h) && (v.m == w.m)) return 1;
	return 0;

};

#endif
