#pragma once
#include "List.h"
#include "ListAtr.h"
#include <iostream>
using namespace std;

struct Blok {
	List selektory;
	ListAtr atrybuty;

	// i want list to stay default
	// based on their own constructors
	Blok() {}

	Blok(List sel, ListAtr atr) {
		selektory = move(sel);
		atrybuty = move(atr);
	}
	Blok(const Blok& b) {
		*this = b;
	}
	Blok(Blok&& b) {
		*this = move(b);
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
		selektory = move(b.selektory);
		atrybuty = move(b.atrybuty);
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