#pragma once
#include "Node.h"

class List
{
protected:
	Node* FirstNode;
	Node* LastNode;
	int size;
	friend class Node2W;
public:
	//static int licznik;
	List();
	List(const List& other);
	List(List&& other);
	void add(const String& val);
	int find(const String& val);
	Node& find(const String& val, bool wantNode);
	bool del(const int& id);
	bool isEmpty();
	void clear();
	int getSize();
	~List();

	Node& operator[](size_t index);
	const Node& operator[](size_t index) const;
	List& operator=(const List& l);
	List& operator=(List&& l);
};
//int List::licznik = 0;