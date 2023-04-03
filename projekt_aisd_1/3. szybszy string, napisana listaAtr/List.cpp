#pragma once
#include "List.h"
#include <iostream>

List::List() {
	FirstNode = LastNode = nullptr;
	size = 0;
}
List::List(const List& other) {
	*this = other;
}
List::List(List&& other) {
	*this = std::move(other);
}
int List::getSize() {
	return this->size;
}
void List::add(const String& val) {
	if (this->FirstNode == nullptr) {
		FirstNode = LastNode = new Node;
		FirstNode->setVal(val);
		this->size++;
		return;
	}

	/*
	Node* tmp = this->FirstNode;
	while (tmp->getNext() != nullptr)
		tmp = tmp->getNext();

	tmp->setNext(new Node);
	tmp = tmp->getNext();
	tmp->setVal(val);
	tmp->setNext(nullptr);
	this->size++;
	*/

	LastNode->setNext(new Node);
	LastNode = LastNode->getNext();
	LastNode->setVal(val);
	LastNode->setNext(nullptr);
	this->size++;
}
bool List::del(const int& id) {
	if (this == nullptr || id >= this->size || id < 0)
		return 0;

	if (id == 0) {
		Node* tmp = this->FirstNode;
		FirstNode = tmp->getNext();
		tmp->setNext(nullptr);
		delete tmp;
		this->size--;
		return 1;
	}
	
	Node* tmp = &(*this)[id-1];
	Node *toAttach = tmp->getNext()->getNext();

	tmp->getNext()->setNext(nullptr);
	delete tmp->getNext();
	tmp->setNext(toAttach);

	if (toAttach == nullptr)		//if deleted node was the last one
		LastNode = tmp;
	this->size--;
	return 1;
}
List::~List() {
	delete FirstNode;
}
int List::find(const String& val) {
	if (FirstNode == nullptr)
		return -1;

	Node* tmp = FirstNode;
	int id = 0;
	while (tmp->getNext() != nullptr && tmp->getVal() != val) {
		tmp = tmp->getNext();
		id++;
	}
	
	if (tmp->getNext() == nullptr && tmp->getVal() != val) {
		return -1;
	}
	return id;
}
Node& List::operator[](size_t index) {
	Node* tmp = this->FirstNode;
	for (std::size_t i = 0; i < index && tmp != nullptr; i++) {
		tmp = tmp->getNext();
	}
	return *tmp;
}
const Node& List::operator[](size_t index) const {
	Node* tmp = this->FirstNode;
	for (std::size_t i = 0; i < index && tmp != nullptr; i++) {
		tmp = tmp->getNext();
	}
	return *tmp;
}
List& List::operator=(const List& l) {
	this->size = l.size;

	if (this->size == 0) {
		FirstNode = LastNode = nullptr;
		return *this;
	}

	FirstNode = new Node;
	FirstNode->setVal(l.FirstNode->getVal());

	Node* tmp = FirstNode;

	for (size_t i = 1; i < this->size; i++) {
		tmp->setNext(new Node);
		tmp = tmp->getNext();
		tmp->setVal(l[i].getVal());
	}
	LastNode = tmp;
	return *this;
}
List& List::operator=(List&& l) {
	this->size = l.size;
	this->FirstNode = l.FirstNode;
	this->LastNode = l.LastNode;
	l.FirstNode = nullptr;
	return *this;
}