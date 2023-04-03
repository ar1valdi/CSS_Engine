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

	if (tmp->getLicznik() + tmp->getDeleted() >= T) {
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

	if (this == nullptr || index >= this->size || index < 0)
		return 0;

	Node2W* tmp = FirstNode;
	int freeSpaces = 0;

	size_t i = 0;
	do {

		freeSpaces += tmp->getDeleted();

		if ((i + 1) * T - freeSpaces > index)
			break;

		if (tmp->getNext() != nullptr)
			tmp = tmp->getNext();
		i++;

	} while (tmp->getNext() != nullptr);

	freeSpaces -= tmp->getDeleted();
	index = (index + freeSpaces) % T;

	size_t fullSpaces = 0;

	for (size_t i = 0; i < T; i++) {
		if (!tmp->getVal(i).selektory.isEmpty())
			fullSpaces++;
		else
			continue;
		if (fullSpaces - 1 == index) {
			tmp->delVal(i);
			break;
		}
	}

	//tmp->delVal(index % T);
	size--;

	if (tmp->getDeleted() == 8)		//deleting empty blocks
	{
		if (tmp->getPrev() != nullptr)
			tmp->getPrev()->setNext(tmp->getNext());
		else
			FirstNode = FirstNode->getNext();
	
		if (tmp->getNext() != nullptr)
			tmp->getNext()->setPrev(tmp->getPrev());
		else if (tmp->getPrev() != nullptr)
			tmp->getPrev()->setNext(nullptr);
	
		if (tmp == LastNode)
			LastNode = LastNode->getPrev();
		tmp->setNext(nullptr);
		tmp->setPrev(nullptr);
		delete tmp;
	}

	return 1;

	//return 1;
}
void List2W::print() {

	for (int i = 0; i < this->size; i++) {

		if (i == 4)
			int x = 0;

		cout << i+1 << ":\n" <<"selektory:\n";
		List* tab = &(*this)[i].selektory;
		for (int j = 0; j < tab->getSize(); j++) {
			cout << (*tab)[j] << " ";
		}

		ListAtr* tabAtr = &(*this)[i].atrybuty;
		cout << "\natrybuty:\n";
		for (int j = 0; j < tabAtr->getSize(); j++) {
			cout << (*tabAtr)[j] << "\n";
		}
		cout << '\n';
	}
}
List2W::~List2W() {
	delete FirstNode;
}
const Blok& List2W::operator[](size_t index) const {

	if (index >= this->size || index < 0)
		throw std::invalid_argument("index out of bound");

	Node2W* tmp = FirstNode;
	int freeSpaces = 0;

	for (size_t i = 0; 1; i++) {
		freeSpaces += tmp->getDeleted();
		if ((i + 1) * T - freeSpaces > index)
			break;
		if (tmp->getNext() != nullptr)
			tmp = tmp->getNext();
		else
			break;
	}

	freeSpaces -= tmp->getDeleted();
	index = (index + freeSpaces) % T;

	size_t fullSpaces = 0;

	for (size_t i = 0; i < T; i++) {
		if (!tmp->getVal(i).selektory.isEmpty())
			fullSpaces++;
		else
			continue;
		if (fullSpaces - 1 == index)
			return tmp->getVal(i);
	}
	return tmp->getVal(T-1);
}
Blok& List2W::operator[](size_t index) {
	if (index >= this->size || index < 0)
		throw std::invalid_argument("index out of bound");

	Node2W* tmp = FirstNode;
	int freeSpaces = 0;

	size_t i = 0;
	do {

		freeSpaces += tmp->getDeleted();

		if ((i + 1) * T - freeSpaces > index)
			break;

		if (tmp->getNext() != nullptr)
			tmp = tmp->getNext();
		i++;

	} while (tmp->getNext() != nullptr);

	freeSpaces -= tmp->getDeleted();
	index = (index + freeSpaces) % T;

	size_t fullSpaces = 0;

	for (size_t i = 0; i < T; i++) {
		if (!tmp->getVal(i).selektory.isEmpty())
			fullSpaces++;
		else
			continue;
		if (fullSpaces - 1== index)
			return tmp->getVal(i);
	}
	return tmp->getVal(T-1);
}
String List2W::lastOccOfAtr(const String& sel, const String& atr) {
	String empty;
	if (sel.getVal() == nullptr ||
		atr.getVal() == nullptr ||
		this->LastNode == nullptr)
			return move(empty);
		//throw runtime_error("not found");

	Node2W* tmp = this->LastNode;

	for (int i = 0; i < this->size; i++) {
		for (int j = tmp->getLicznik() - 1; j >= 0; j--) {

			List* tmp2 = &tmp->getSel(j);

			if (tmp2->find(sel) != -1 ||
				(tmp2->getSize() == 1 && (*tmp2)[0].getVal() == "")) {
				try {
					return tmp->getAtr(j).find(atr, 1).getValV();
				}
				catch (runtime_error e) {}
			}
		}
		if (tmp->getPrev() != nullptr)
			tmp = tmp->getPrev();
		else
			break;
	}

	return move(empty);
	//throw runtime_error("not found");
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