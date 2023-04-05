#pragma once
#include "ListAtr.h"
#include <iostream>

ListAtr::ListAtr() {	//
	FirstNode = LastNode = nullptr;
	size = 0;
}
ListAtr::ListAtr(const ListAtr& other) {	//
	*this = other;
}
ListAtr::ListAtr(ListAtr&& other) {	//
	*this = std::move(other);
}
int ListAtr::getSize() {	//
	return this->size;
}
bool ListAtr::isEmpty() {
	if (this == nullptr || this->FirstNode == nullptr)
		return 1;
	return 0;
}
void ListAtr::add(const String& atr, const String& val) {	//
	if (this->FirstNode == nullptr) {
		FirstNode = LastNode = new NodeAtr;
		FirstNode->setValV(val);
		FirstNode->setValA(atr);
		this->size++;
		return;
	}

	LastNode->setNext(new NodeAtr);
	LastNode = LastNode->getNext();
	LastNode->setValV(val);
	LastNode->setValA(atr);
	LastNode->setNext(nullptr);
	this->size++;
}
void ListAtr::clear() {
	FirstNode = nullptr;
	LastNode = nullptr;
	size = 0;
}
bool ListAtr::del(const int& id) {	//
	if (this == nullptr || id >= this->size || id < 0)
		return 0;

	if (id == 0) {
		NodeAtr* tmp = this->FirstNode;
		FirstNode = tmp->getNext();
		tmp->setNext(nullptr);
		delete tmp;
		this->size--;
		return 1;
	}

	NodeAtr* tmp = &(*this)[id - 1];
	NodeAtr* toAttach = tmp->getNext()->getNext();

	tmp->getNext()->setNext(nullptr);
	delete tmp->getNext();
	tmp->setNext(toAttach);

	if (toAttach == nullptr)		//if deleted node was the last one
		LastNode = tmp;
	this->size--;
	return 1;
}
int ListAtr::find(const String& val) {	//
	if (FirstNode == nullptr)
		return -1;

	NodeAtr* tmp = FirstNode;
	int id = 0;
	while (tmp->getNext() != nullptr && tmp->valA != val) {
		tmp = tmp->getNext();
		id++;
	}

	if (tmp->getNext() == nullptr && tmp->valA != val) {
		return -1;
	}
	return id;
}
NodeAtr& ListAtr::find(const String& val, bool wantNode) {
	NodeAtr emptyNode;
	if (FirstNode == nullptr)
		return emptyNode;

	NodeAtr* tmp = FirstNode;
	int id = 0;
	while (tmp->getNext() != nullptr && tmp->valA != val) {
		tmp = tmp->getNext();
	}

	if (tmp->getNext() == nullptr && tmp->valA != val)
		return emptyNode;

	return *tmp;
}
NodeAtr& ListAtr::operator[](size_t index) {		//
	NodeAtr* tmp = this->FirstNode;
	for (std::size_t i = 0; i < index && tmp != nullptr; i++) {
		tmp = tmp->getNext();
	}
	return *tmp;
}
const NodeAtr& ListAtr::operator[](size_t index) const {		//
	NodeAtr* tmp = this->FirstNode;
	for (std::size_t i = 0; i < index && tmp != nullptr; i++) {
		tmp = tmp->getNext();
	}
	return *tmp;
}
ListAtr& ListAtr::operator=(const ListAtr& l) {	// nie uzywam ??
	this->size = l.size;

	if (this->size == 0) {
		FirstNode = LastNode = nullptr;
		return *this;
	}

	if (FirstNode != nullptr)
		delete FirstNode;
	FirstNode = new NodeAtr;
	FirstNode->setValV(l.FirstNode->getValV());
	FirstNode->setValA(l.FirstNode->getValA());

	NodeAtr* tmp = FirstNode;

	for (size_t i = 1; i < this->size; i++) {
		tmp->setNext(new NodeAtr);
		tmp = tmp->getNext();

		tmp->setValV(l[i].getValV());
		tmp->setValA(l[i].getValA());
	}
	LastNode = tmp;
	return *this;
}
ListAtr& ListAtr::operator=(ListAtr&& l) {	//
	this->size = l.size;
	this->FirstNode = l.FirstNode;
	this->LastNode = l.LastNode;
	l.FirstNode = nullptr;
	l.LastNode = nullptr;
	return *this;
}
void ListAtr::print() {	//
	cout << "Size = " << size << '\n';
	for (int i = 0; i < size; i++) {
		cout << "Atr: " << (*this)[i].getValA().getVal() << ' ';
		cout << "Value: " << (*this)[i].getValV().getVal() << '\n';
	}
}
ListAtr::~ListAtr() {	//
	if (this != nullptr && FirstNode != nullptr)
		delete FirstNode;
}