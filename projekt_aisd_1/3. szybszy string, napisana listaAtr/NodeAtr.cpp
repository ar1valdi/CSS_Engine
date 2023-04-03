#pragma once
#include "NodeAtr.h"
#include <iostream>

NodeAtr::NodeAtr() {
	this->valV = "";
	this->valA = "";
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
NodeAtr::~NodeAtr() {
	if (next != nullptr)
		delete next;
}