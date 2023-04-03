#pragma once
#include "List.h"
#include "ListAtr.h"
#include <iostream>
using namespace std;

struct Blok {
	List selektory;
	ListAtr atrybuty;

	void clear() {
		List empty;
		ListAtr emptyAtr;
		selektory = empty;
		atrybuty = emptyAtr;
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
	Blok() {}		
	// i want list to stay default
	// based on their own constructors
};