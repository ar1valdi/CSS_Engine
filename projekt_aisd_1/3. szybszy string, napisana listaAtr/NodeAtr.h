#pragma once
#include "String.h"
using namespace std;

class NodeAtr
{
protected:
	String valA;
	String valV;
	NodeAtr* next;
	friend ostream& operator<<(ostream& out, const NodeAtr& n);
public:
	NodeAtr();
	NodeAtr(const NodeAtr& right);
	NodeAtr(NodeAtr&& right);
	const String getValA() const;
	const String getValV() const;
	void setValA(const String& newV);
	void setValV(const String& newV);
	NodeAtr* getNext();
	void setNext(NodeAtr* newN);
	~NodeAtr();

	NodeAtr& operator=(NodeAtr* other) {
		valA = other->valA;
		valV = other->valV;
		next = other->next;
		return *this;
	}
};