#pragma once
#include "Move.h"
#include "Node.h"
#include <iostream>

Node::Node() {
	this->next = nullptr;
}
Node::Node(const Node& right) {
	val = right.val;
	next = right.next;
}
Node::Node(Node&& right) {
	val = Move<String>(right.val);
	next = right.next;
}
const String Node::getVal() const{
	return this->val;
}
void Node::setVal(const String& newV) {
	this->val = newV;
}
Node* Node::getNext() {
	return this->next;
}
void Node::setNext(Node* newN) {
	this->next = newN;
}
Node::~Node() {
	if(this != nullptr && next != nullptr)
		delete next;
}