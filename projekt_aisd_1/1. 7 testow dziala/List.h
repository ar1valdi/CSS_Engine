#pragma once
#include "Node.h"
class List
{
protected:
	Node* FirstNode;
	int size;
public:
	List();
	List(const List& other);
	List(List&& other);
	void add(const String& val);
	int find(const String& val);
	bool del(const int& id);
	int getSize();
	~List();

	Node& operator[](size_t index);
	const Node& operator[](size_t index) const;
	List& operator=(const List& l);
	List& operator=(List&& l);
};