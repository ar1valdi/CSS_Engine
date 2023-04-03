#pragma once
#include "List.h"
#include <iostream>
using namespace std;

struct Blok {
	List selektory;
	List atrybuty;
	List wartosci;

	void clear() {
		List empty;
		selektory = atrybuty = wartosci = empty;
	}

	Blok& operator=(const Blok& b) {
		selektory = b.selektory;
		atrybuty = b.atrybuty;
		wartosci = b.wartosci;
		return *this;
	}
	Blok& operator=(Blok&& b) {
		selektory = move(b.selektory);
		atrybuty = move(b.atrybuty);
		wartosci = move(b.wartosci);
		return *this;
	}
	Blok(List sel, List atr, List war) {
		selektory = move(sel);
		atrybuty = move(atr);
		wartosci = move(war);
	}
	Blok(const Blok& b) {
		*this = b;
	}
	Blok(Blok&& b) {
		*this = move(b);
	}
	Blok() {
		List empty;
		selektory = atrybuty = wartosci = empty;
	}
};