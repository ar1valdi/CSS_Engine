#pragma once
#include <iostream>
#include "blok.h"
#include "NodeAtr.h"

ostream& operator<<(ostream& out, Blok& b) {
	cout << "selektory:\n";
	for (int i = 0; i < b.selektory.getSize(); i++)
		out << b.selektory[i] << ", ";
	cout << "\natrybuty:\n";
	for (int i = 0; i < b.atrybuty.getSize(); i++) {
	//	out << b.atrybuty[i].print();
	}
	cout << endl;
	return out;
}
ostream& operator<<(std::ostream& out, const String& s) {
	if (s.getVal() != nullptr)
		out << s.getVal();
	return out;
}
ostream& operator<<(ostream& out, const Node& n) {
	if(n.val != nullptr)
		out << n.val;
	return out;
}
ostream& operator<<(ostream& out, const NodeAtr& n) {
	if (n.valV != nullptr && n.valA != nullptr)
		out << n.valA << " : " << n.valV;;
	return out;
}