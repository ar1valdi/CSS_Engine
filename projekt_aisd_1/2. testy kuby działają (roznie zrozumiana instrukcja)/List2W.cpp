#pragma once
#include "List2W.h"
#include <iostream>

List2W::List2W() {
	FirstNode = nullptr;
	LastNode = nullptr;
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
		LastNode = FirstNode;
		this->size++;
		return;
	}

	Node2W* tmp = this->LastNode;
	//Node2W* tmp = this->FirstNode;
	//while (tmp->getNext() != nullptr && tmp->getLicznik() <= T)
	//	tmp = tmp->getNext();

	if (tmp->getLicznik() >= T) {
		tmp->setNext(new Node2W);
		tmp->getNext()->setPrev(tmp);
		tmp = tmp->getNext();
		tmp->addVal(val);
		tmp->setNext(nullptr);
		this->LastNode = tmp;
	}
	else
		tmp->addVal(val);
	this->size++;
}
bool List2W::del(int index) {
	//usunac
	if (this->size == 7)
		int x = 0;

	if (this == nullptr || index >= this->size || index < 0)
		return 0;

	Node2W* tmp = FirstNode;

	if (!(index < T && tmp->getLicznik() > index)){
		for (std::size_t i = T - 1; i <= index && tmp->getNext() != nullptr; i += T) {
			index += T - tmp->getLicznik();
			if (i >= index)
				break;
			tmp = tmp->getNext();
		}
	}

	tmp->delVal(index % T);
	if (tmp->getLicznik() == 0)
	{
		if (tmp->getPrev() != nullptr)
			tmp->getPrev()->setNext(tmp->getNext());
		else
			FirstNode = FirstNode->getNext();

		if (tmp->getNext() != nullptr)
			tmp->getNext()->setPrev(tmp->getPrev());
		else if (tmp->getPrev() != nullptr)
			tmp->getPrev()->setNext(nullptr);

		if(tmp == LastNode)
			LastNode = LastNode->getPrev();
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
	if (index >= this->size || index < 0)
		throw std::invalid_argument("index out of bound");

	Node2W* tmp = this->FirstNode;
	if (index < T && tmp->getLicznik() > index)
		return tmp->getVal(index);

	for (std::size_t i = T - 1; i <= index && tmp->getNext() != nullptr; i += T) {
		index += T - tmp->getLicznik();
		if (i >= index)
			break;
		tmp = tmp->getNext();
	}
	return tmp->getVal(index % T);
}
Blok& List2W::operator[](size_t index) {
	if (index >= this->size || index < 0)
		throw std::invalid_argument("index out of bound");

	Node2W* tmp = this->FirstNode;
	if (index < T && tmp->getLicznik() > index)
		return tmp->getVal(index);

	for (std::size_t i = T-1; i <= index && tmp->getNext() != nullptr; i += T) {
		index += T - tmp->getLicznik();
		if (i >= index)
			break;
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

	FirstNode = LastNode = new Node2W;
	FirstNode->addVal(other[0]);
	Node2W* tmp = FirstNode;
	for (size_t i = 1; i < other.size; i++)
		this->add(other[i]);
	return *this;
}
List2W& List2W::operator=(List2W&& other) {
	this->size = other.size;
	this->FirstNode = other.FirstNode;
	this->LastNode = other.LastNode;
	other.FirstNode = nullptr;
	return *this;
}
int List2W::getSizeAct() {
	Node2W* tmp = FirstNode;

	if (tmp == nullptr)
		return 0;

	int licz = tmp->getLicznik();

	while (tmp->getNext() != nullptr) {
		tmp = tmp->getNext();
		licz += tmp->getLicznik();
		if (licz > 1290)
			int x = 0;
	}
	return licz;
}