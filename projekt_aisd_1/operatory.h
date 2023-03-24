#include <iostream>
#include "blok.h"

ostream& operator<<(ostream& out, Blok& b) {
	cout << "selektory:\n";
	for (int i = 0; i < b.selektory.getSize(); i++)
		out << b.selektory[i] << ", ";
	cout << "\natrybuty:\n";
	for (int i = 0; i < b.atrybuty.getSize(); i++) {
		out << b.atrybuty[i] << " : " << b.wartosci[i] << "\n";
	}
	cout << endl;
	return out;
}
std::ostream& operator<<(std::ostream& out, const String& s) {
	if (s.getVal() != nullptr)
		out << s.getVal();
	return out;
}
ostream& operator<<(ostream& out, const Node& n) {
	if(n.val != nullptr)
		out << n.val;
	return out;
}