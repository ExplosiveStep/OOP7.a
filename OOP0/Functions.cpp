#include "Header.h"
#include <iostream>
#include <fstream>

using namespace std;

//������� ���������� �� ���������
void container::Clear(container* head) {
    int len = head->len;
    container* temp = head;
    for (int i = 0; i < len; i++) {
        delete temp->cont;
        temp->len = 0;
        temp = temp->next;
    }
    for (int i = 0; i < len; i++) {

        temp = head->next;
        delete head;
        head = temp;
    }
}

// ���� ����������� ���������� �� ���������� ������
void container::In(ifstream& ifst, container* head, container* tail) {
    container* temp;
    int Len = 0;
    while (!ifst.eof()) {

        switch (Len)
        {
        case 0:
            if ((head->cont = transport::In(ifst))) {
                Len++;
            }
            break;

        case 1:
            if ((tail->cont = transport::In(ifst))) {
                head->next = tail;
                head->prev = tail;
                tail->next = head;
                tail->prev = head;
                Len++;
            }
            break;

        default:
            temp = new container;
            temp->next = NULL;
            temp->prev = NULL;
            if ((temp->cont = transport::In(ifst))) {
                tail->next = temp;
                head->prev = temp;
                temp->next = head;
                temp->prev = tail;
                tail = temp;
                Len++;
            }
            break;
        }
        temp = head;
        for (int i = 0; i < Len; i++) {
            temp->len = Len;
            temp = temp->next;
        }
    }
}
// ���� ���������� �� �����
transport* transport::In(ifstream& ifst) {
	transport* sp;
	int k;
	ifst >> k;
	switch (k) {
	case 1:
		sp = new truck;
		break;
	case 2:
		sp = new bus;
		break;
	default:
		return 0;
	}
	sp->InData(ifst);
	return sp;
}

// ���� ���������� ��������� �� �����
void truck::InData(ifstream& ifst) {
	ifst >> cargo >> engine;
}

// ���� ���������� �������� �� �����
void bus::InData(ifstream& ifst) {
	ifst >> capacity >> engine;
}

// ����� ���������� � ����
void container::Out(ofstream& ofst, container* head) {

    int len = head->len;
    container* temp = head;
    ofst << "Container contains " << head->len
        << " elements." << endl;
    for (int i = 0; i < len; i++) {
        ofst << i << ": ";
        temp->cont->Out(ofst);
        temp = temp->next;
    }
}

// ����� ���������� ���������� ����
void truck::Out(ofstream& ofst) {
    ofst << "It is truck: cargo = " << cargo << ", engine = " << engine << endl;
}

// ����� ���������� �������� ����
void bus::Out(ofstream& ofst) {
    ofst << "It is bus: capacity = " << capacity << ", engine = " << engine << endl;
}

int container::Getlen()
{
    return len;
}

// �����������
void bus::MultiMethod(transport* other, ofstream& ofst) {
    other->MMBus(ofst);
}

// �����������
void truck::MultiMethod(transport* other, ofstream& ofst) {
    other->MMTruck(ofst);
}

// ����� ���� ���������
void bus::MMBus(ofstream& ofst) {
    ofst << "Bus and Bus" << endl;
}

// ����� ��������� � ��������
void bus::MMTruck(ofstream& ofst) {
    ofst << "Truck and Bus" << endl;
}

// ����� �������� � ���������
void truck::MMBus(ofstream& ofst) {
    ofst << "Bus and Truck" << endl;
}

// ����� ���� ����������
void truck::MMTruck(ofstream& ofst) {
    ofst << "Truck and Truck" << endl;
}

// ����� ������������ ��� ��������� ����������
void container::MultiMethod(container* head, ofstream & ofst) {
    container* First = head;
    container* Second = head->next;
    int len = head->len;

    for (int i = 0; i < len - 1; i++) {

        for (int j = i + 1; j < len; j++) {
            First->cont->MultiMethod(Second->cont, ofst);
            First->cont->Out(ofst);
            Second->cont->Out(ofst);
            Second = Second->next;
        }
        First = First->next;
        Second = First->next;
    }
}