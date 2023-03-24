#pragma once
#include "List2W.h"
#include <iostream>

List2W::List2W() {
	FirstNode = nullptr;
	size = 0;
}
List2W::List2W(const List2W& other) {
	*this = other;
}
List2W::List2W(List2W&& other) {
	*this = move(other);
}
int List2W::getSize() {
	return this->size;
}
void List2W::add(const Blok& val) {
	if (this->FirstNode == nullptr) {
		FirstNode = new Node2W;
		FirstNode->addVal(val);
		this->size++;
		return;
	}

	Node2W* tmp = this->FirstNode;
	while (tmp->getNext() != nullptr && tmp->getLicznik() < T)
		tmp = tmp->getNext();

	if (tmp->getLicznik() >= T) {
		tmp->setNext(new Node2W);
		tmp->getNext()->setPrev(tmp);
		tmp = tmp->getNext();
		tmp->addVal(val);
		tmp->setNext(nullptr);
	}
	else
		tmp->addVal(val);
	this->size++;
}
bool List2W::del(const int& index) {
	if (index >= this->size || index < 0)
		return 0;
	
	Node2W* tmp = FirstNode;
	for (std::size_t i = 0; i <= index && tmp->getNext() != nullptr; i += T) {
		tmp = tmp->getNext();
	}

	tmp->delVal(index % T);
	if (tmp->getLicznik() == 0)
	{
		tmp->getPrev()->setNext(tmp->getNext());
		tmp->getNext()->setPrev(tmp->getPrev());
		tmp->setNext(nullptr);
		tmp->setPrev(nullptr);
		delete tmp;
	}
	size--;
	return 1;
}
List2W::~List2W() {
	delete FirstNode;
}
const Blok& List2W::operator[](size_t index) const {
	Node2W* tmp = this->FirstNode;
	for (std::size_t i = T - 1; i < index && tmp->getNext() != nullptr; i += T) {
		tmp = tmp->getNext();
	}
	return tmp->getVal(index%T);
}
Blok& List2W::operator[](size_t index) {
	Node2W* tmp = this->FirstNode;
	for (std::size_t i = T-1; i < index && tmp->getNext() != nullptr; i += T) {
 		tmp = tmp->getNext();
	}
	return tmp->getVal(index%T);
}
List2W& List2W::operator=(const List2W& other) {
	this->size = other.size;
	if (this->size == 0) {
		FirstNode = nullptr;
		return *this;
	}

	FirstNode = new Node2W;
	FirstNode->addVal(other[0]);
	Node2W* tmp = FirstNode;
	for (size_t i = 1; i < this->size; i++)
		this->add(other[i]);
	return *this;
}
List2W& List2W::operator=(List2W&& other) {
	this->size = other.size;
	this->FirstNode = other.FirstNode;
	other.FirstNode = nullptr;
	return *this;
}