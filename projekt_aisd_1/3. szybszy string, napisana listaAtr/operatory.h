#include <iostream>
#include "blok.h"
#include "NodeAtr.h"

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
		out << n.valV << " " << n.valA;;
	return out;
}
String operator+(const char c, const String& s) {
	String result;
	result.val = new char[s.size + 1];
	result.val[0] = c;
	result.size = s.size + 1;

	for (int i = 1; i < result.size; i++)
		result.val[i] = s.val[i - 1];
	return result;
}