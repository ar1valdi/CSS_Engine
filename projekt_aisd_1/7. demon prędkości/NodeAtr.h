#pragma once
#include "String.h"
using namespace std;

class NodeAtr
{
protected:
	NodeAtr* next;
	friend ostream& operator<<(ostream& out, const NodeAtr& n);
	//friend class ListAtr;
public:
	String valA;
	String valV;
	NodeAtr();
	NodeAtr(const NodeAtr& right);
	NodeAtr(NodeAtr&& right);
	const String getValA() const;
	String& getValAref();
	const String getValV() const;
	void setValA(const String& newV);
	void setValV(const String& newV);
	bool isEmpty();
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