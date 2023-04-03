#pragma once
#include "NodeAtr.h"
class ListAtr
{
protected:
	NodeAtr* FirstNode;
	NodeAtr* LastNode;
	int size;
public:
	ListAtr();
	ListAtr(const ListAtr& other);
	ListAtr(ListAtr&& other);
	void add(const String& atr, const String& val);
	int find(const String& val);
	bool del(const int& id);
	int getSize();
	void print();
	~ListAtr();

	NodeAtr& operator[](size_t index);
	const NodeAtr& operator[](size_t index) const;
	ListAtr& operator=(const ListAtr& l);
	ListAtr& operator=(ListAtr&& l);
};