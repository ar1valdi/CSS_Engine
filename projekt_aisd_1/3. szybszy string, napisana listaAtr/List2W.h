#pragma once
#include "Node2W.h"

class List2W
{
private:
	Node2W* FirstNode;
	Node2W* LastNode;
	int size;
public:
	List2W();
	List2W(List2W&& right);
	List2W(const List2W& right);
	~List2W();

	void add(const Blok& val);
	bool del(int index);
	int getSize();

	Blok& operator[](size_t index);
	const Blok& operator[](size_t index) const;
	List2W& operator=(const List2W& other);
	List2W& operator=(List2W&& other);
};

