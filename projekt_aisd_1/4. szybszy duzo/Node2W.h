#pragma once
#define T 8
#include "Blok.h"
using namespace std;

class Node2W
{
private:
	Blok val[T];
	int licznik, deleted;
	Node2W* next;
	Node2W* prev;
public:
	Node2W();
	Node2W(const Node2W& right);
	Node2W(Node2W&& right);

	Blok& getVal(int id);
	List& getSel(int id);
	ListAtr& getAtr(int id);
	int getLicznik();
	int getDeleted();
	bool addVal(const Blok& newV);
	bool delVal(int id);
	Node2W* getNext();
	void setNext(Node2W* newN);
	Node2W* getPrev();
	void setPrev(Node2W* newP);
	~Node2W();

	Node2W& operator=(Node2W* other) {
		for (int i = 0; i < other->licznik; i++)
			val[i] = other->val[i];
		next = other->next;
		this->licznik = other->licznik;
		return *this;
	}
};