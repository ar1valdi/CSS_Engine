#pragma once
#include "Node.h"
#include <iostream>

Node::Node() {
	this->val = "";
	this->next = nullptr;
}
Node::Node(const Node& right) {
	val = right.val;
	next = right.next;
}
Node::Node(Node&& right) {
	val = move(right.val);
	next = move(right.next);
}
const String Node::getVal() const{
	return this->val;
}
void Node::setVal(String newV) {
	this->val = newV;
}
Node* Node::getNext() {
	return this->next;
}
void Node::setNext(Node* newN) {
	this->next = newN;
}
Node::~Node() {
	if(next != nullptr)
		delete next;
}