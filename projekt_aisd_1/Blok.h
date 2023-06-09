#pragma once
#include "List.h"
#include "ListAtr.h"
#include <iostream>
#include "Move.h"
using namespace std;

struct Blok {
	List selektory;
	ListAtr atrybuty;

	// i want list to stay default
	// based on their own constructors
	Blok() {}

	Blok(List sel, ListAtr atr) {
		selektory = Move<List>(sel);
		atrybuty = Move<ListAtr>(atr);
	}
	Blok(const Blok& b) {
		*this = b;
	}
	Blok(Blok&& b) {
		*this = Move<Blok>(b);
	}

	void clear() {
		atrybuty.clear();
		selektory.clear();
	}

	Blok& operator=(const Blok& b) {
		selektory = b.selektory;
		atrybuty = b.atrybuty;
		return *this;
	}
	Blok& operator=(Blok&& b) {
		selektory = Move<List>(b.selektory);
		atrybuty = Move<ListAtr>(b.atrybuty);
		return *this;
	}
	~Blok() {
		// both lists are deleted automatically
	}
	bool isEmpty() {
		if (selektory.FirstNode == nullptr || atrybuty.FirstNode == nullptr)
			return 1;
		return 0;
	}
};