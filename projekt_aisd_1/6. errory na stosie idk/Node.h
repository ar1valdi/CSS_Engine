#pragma once
#include "String.h"
using namespace std;

class Node
{
protected:
	String val;
	Node* next;
	friend ostream& operator<<(ostream& out, const Node& n);
	friend class List;
public:
	Node();
	Node(const Node& right);
	Node(Node&& right);
	const String getVal() const;
	void setVal(const String& newV);
	Node* getNext();
	void setNext(Node* newN);
	~Node();

	Node& operator=(Node* other) {
		val = other->val;
		next = other->next;
		return *this;
	}
};