#pragma once
#include "NodeAtr.h"
#include <iostream>

NodeAtr::NodeAtr() {
	this->next = nullptr;
}
NodeAtr::NodeAtr(const NodeAtr& right) {
	valV = right.valV;
	valA = right.valA;
	next = right.next;
}
NodeAtr::NodeAtr(NodeAtr&& right) {
	valV = move(right.valV);
	valA = move(right.valA);
	next = move(right.next);
}
const String NodeAtr::getValV() const {
	return this->valV;
}
const String NodeAtr::getValA() const {
	return this->valA;
}
void NodeAtr::setValV(const String& newV) {
	this->valV = newV;
}
void NodeAtr::setValA(const String& newV) {
	this->valA = newV;
}
NodeAtr* NodeAtr::getNext() {
	return this->next;
}
void NodeAtr::setNext(NodeAtr* newN) {
	this->next = newN;
}
bool NodeAtr::isEmpty() {
	if (valA.getSize() <= 0)
		return 1;
	return 0;
}
NodeAtr::~NodeAtr() {
	if (next != nullptr)
		delete next;
}
String& NodeAtr::getValAref() {
	return this->valA;
}