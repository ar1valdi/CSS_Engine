#pragma once
#include "List2W.h"
#include <iostream>

List2W::List2W() {
	FirstNode = nullptr;
	LastNode = nullptr;
	size = 0;
}
int List2W::getSize() {
	return this->size;
}
int List2W::instancesOfAtr(const String& atr) {
	if (atr.getSize() <= 1 || this == nullptr || this->FirstNode == nullptr)
		return -1;

	int num = 0;
	Node2W* tmp = FirstNode;
	int freeSpaces = FirstNode->getDeleted();

	for (int j = 0; j * T < this->size + freeSpaces; j++) {
		for (int i = 0; i < T; i++) {
			if (!tmp->getAtr(i).isEmpty()) {
				if (tmp->getAtr(i).find(atr) != -1)
					num++;
			}
		}
		tmp = tmp->getNext();
		if(tmp != nullptr)
			freeSpaces += tmp->getDeleted();
	}
	return num;
}
int List2W::instancesOfSel(const String& sel) {
	if (sel.getSize() <= 1 || this == nullptr || this->FirstNode == nullptr)
		return -1;

	int num = 0;
	Node2W* tmp = FirstNode;
	int freeSpaces = FirstNode->getDeleted();

	for (int j = 0; j * T < this->size + freeSpaces; j++) {
		for (int i = 0; i < T; i++) {
			if (!tmp->getSel(i).isEmpty()) {
				if (tmp->getSel(i).find(sel) != -1)
					num++;
			}
		}
		if (j != 0)
			freeSpaces += tmp->getDeleted();
		tmp = tmp->getNext();
	}
	return num;
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

	// if new block has to be created
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
	int freeSpaces = tmp->getDeleted();

	size_t i = 0;
	while ((i+1) * T <= index + freeSpaces) {
		tmp = tmp->getNext();
		freeSpaces += tmp->getDeleted();
		i++;
	}

	freeSpaces -= tmp->getDeleted();
	index = (index + freeSpaces) % T;

	size_t fullSpaces = 0;

	for (size_t j = 0; j < T; j++) {
		if (!tmp->getVal(j).selektory.isEmpty())
			fullSpaces++;
		else
			continue;
		if (fullSpaces - 1 == index) {
			tmp->delVal(j);
			break;
		}
	}

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
}
const Blok& List2W::operator[](size_t index) const {

	if (index >= this->size || index < 0)
		throw std::invalid_argument("index out of bound");

	Node2W* tmp = FirstNode;
	int freeSpaces = 0;

	size_t i = 0;
	while ((i+1) * T <= index + freeSpaces) {
		tmp = tmp->getNext();
		freeSpaces += tmp->getDeleted();
		i++;
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
		else
			break;
		i++;

	} while (1);

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
			return empty;

	Node2W* tmp = this->LastNode;

	for (int i = 0; (i-1) * T < this->size; i++) {
		for (int j = T - 1; j >= 0; j--) {

			while (tmp->getSel(j).isEmpty())
				j--;

			List* tmp2 = &tmp->getSel(j);

			if (tmp2->find(sel) != -1 ||
				(tmp2->getSize() == 1 && (*tmp2)[0].getVal() == "")) {
				NodeAtr* returned = &tmp->getAtr(j).find(atr, 1);

				if (!returned->isEmpty())
					return returned->getValV();
			}
		}
		if (tmp->getPrev() != nullptr)
			tmp = tmp->getPrev();
		else
			break;
	}

	return empty;
}
List2W::~List2W() {
	if (this != nullptr && FirstNode != nullptr)
		delete FirstNode;
}