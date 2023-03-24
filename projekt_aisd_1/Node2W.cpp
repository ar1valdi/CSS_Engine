#pragma once
#include "Node2W.h"
#include "Blok.h"
#include <iostream>

Node2W::Node2W() {
	this->next = nullptr;
	this->prev = nullptr;
	this->licznik = 0;
}
Node2W::Node2W(const Node2W& right) {
	for (int i = 0; i < T; i++)
		val[i] = right.val[i];
	this->licznik = right.licznik;
	next = right.next;
}
Node2W::Node2W(Node2W&& right) {
	for (int i = 0; i < T; i++)
		val[i] = right.val[i];
	this->licznik = right.licznik;
	next = move(right.next);
	prev = move(right.prev);
}
Blok& Node2W::getVal(int id){
	return this->val[id];
}
List& Node2W::getSel(int id) {
	return this->val[id].selektory;
}
List& Node2W::getWar(int id) {
	return this->val[id].wartosci;
}
List& Node2W::getAtr(int id) {
	return this->val[id].atrybuty;
}
bool Node2W::addVal(Blok newV) {
	if (licznik > T)
		return 0;
	val[licznik++] = newV;
	return 1;
}
bool Node2W::delVal(int id) {
	if (id > T-1)
		return 0;
	for (int i = id; i < T - 1; i++)
		val[i] = val[i + 1];
	licznik--;
}
int Node2W::getLicznik() {
	return licznik;
}
Node2W* Node2W::getNext() {
	return this->next;
}
void Node2W::setNext(Node2W* newN) {
	this->next = newN;
}
Node2W* Node2W::getPrev() {
	return this->prev;
}
void Node2W::setPrev(Node2W* newP) {
	this->prev = newP;
}
Node2W::~Node2W() {
	if(next != nullptr)
		delete next;
}