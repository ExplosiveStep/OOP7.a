#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>

using namespace std;

//Обобщение
class transport {
public:
	static transport* In(ifstream& ifst);
	virtual void InData(ifstream& ifst) = 0;
	virtual void Out(ofstream& ofst) = 0;
	virtual void MultiMethod(transport* other, ofstream& ofst) = 0;
	virtual void MMBus(ofstream& ofst) = 0;
	virtual void MMTruck(ofstream& ofst) = 0;
};

//Грузовик
class truck : public transport {
	int cargo;//Грузоподъемность
	int engine;//Мощность двигателя
public:
	void InData(ifstream& ifst);
	void Out(ofstream& ofst);
	void MultiMethod(transport* other, ofstream& ofst);
	void MMBus(ofstream& ofst);
	void MMTruck(ofstream& ofst);
	truck()//Конструктор
	{
		cargo = 0;
		engine = 0;
	}
};

class bus : public transport {
	short int capacity;//Пассажировместимость
	int engine;//Мощность двигателя
public:
	void InData(ifstream& ifst);
	void Out(ofstream& ofst);
	void MultiMethod(transport* other, ofstream& ofst);
	void MMBus(ofstream& ofst);
	void MMTruck(ofstream& ofst);
	bus()//Конструктор
	{
		capacity = 0;
		engine = 0;
	}
};

//Контейнер
class container {
	container* next;
	container* prev;
	transport* cont;
	int len = 0;
public:
	void In(ifstream& ifst, container*, container*);
	void Out(ofstream& ofst, container*);
	void Clear(container*);
	int Getlen();
	void MultiMethod(container* head, ofstream& ofst);
	container()
	{
		next = NULL;
		prev = NULL;
		cont = NULL;
		len = 0;
	}
	~container()
	{
	}
};
#endif