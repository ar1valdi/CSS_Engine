#include "String.h"
#include <iostream>
#define stringBuf 64

String::String() {
	val = new char;
	*val = '\0';
	size = 1;
}
char* String::getVal() const {
	return this->val;
}
void addMemory(char*& t, int size, int newSize) {
	char* buf = t;
	t = new char[newSize];
	for (int i = 0; i < size - 1 && i < newSize; i++)
		t[i] = buf[i];
	if (buf != nullptr)
		delete[] buf;
	t[newSize - 1] = '\0';
}
void String::getline() {
	cleanVal();
	this->val = new char[stringBuf];
	int bufs = 1;

	int ch = EOF;
	size = 0;
	while (ch) {
		ch = getc(stdin);
		if (ch == '\n' || ch == EOF)
			ch = 0;
		
		if (size < stringBuf * bufs)
			val[size++] = ch;
		else {
			bufs++;
			addMemory(this->val, size, bufs*stringBuf);
			val[size++] = ch;
		}
	}

	if (size != stringBuf * bufs) 
		addMemory(this->val, size, size);
}
void String::cleanVal() {
	if (this->val != nullptr)
		delete[] this->val;
	this->val = nullptr;
}
int String::find(char c, int start) const {
	for (int i = start; i < this->size; i++) {
		if (this->val[i] == c)
			return i;
	}
	return -1;
}
void String::erase(int start, int n) {
	int id = start;
	for (int i = start; i+n < this->size; i++) {
		val[i] = val[i + n];
	}
	size -= n;
	char* buf = val;
	val = new char[size];
	for (int i = 0; i < size; i++)
		val[i] = buf[i];
	delete[] buf;
}
int String::getSize() const {
	return this->size;
}
String::~String() {
	if (val != nullptr)
		delete[] val;
}
String::String(const String& other) {
	this->size = 0;
	this->val = nullptr;
	*this = other;
}
String::String(String&& other) {
	this->size = 0;
	this->val = nullptr;
	*this = std::move(other);
}
String::String(const char*&& other) {
	this->size = 0;
	this->val = nullptr;
	*this = other;
}/*
String::String(const char*& other) {
	this->size = 0;
	this->val = nullptr;
	*this = std::move(other);
}*/

char& String::operator[](int i) {
	return this->val[i];
}
String& String::operator=(const char* s) {
	if (s == nullptr) {
		String empty;
		*this = empty;
		return empty;
	}
	int i = 0;
	int s_size = 0;
	while (s[i] != 0 ) {
		s_size++;
		i++;
	}
	s_size++;
	i = 0;
	if (s_size < this->size || s_size > this->size * 2) {
		cleanVal();
		this->val = new char[s_size];
	}
	while (s[i] != 0) {
		this->val[i] = s[i];
		i++;
	}
	this->val[s_size - 1] = 0;
	this->size = s_size;
	return *this;
}
String& String::operator=(const String& s) {
	if (s.size > this->size) {
		cleanVal();
		this->val = new char[s.size];
	}
	this->size = s.size;
	for (int i = 0; i < size; i++)
		val[i] = s.val[i];
	return *this;
}
String& String::operator=(char*&& s) {
	if (s == nullptr) {
		String empty;
		*this = empty;
		return empty;
	}
	this->val = s;
	s = nullptr;
	int i = 0;
	while (val[i] != 0)
	{
		size++;
		i++;
	}
	size++;
	return *this;
}
String& String::operator=(String&& s) {
	this->size = s.size;
	this->val = s.val;
	s.val = nullptr;
	return *this;
}
const bool String::operator==(const String& s) const{
	if (s.val == nullptr && this->val == nullptr)
		return true;
	if (size != s.size || s.val == nullptr)
		return false;
	for (int i = 0; i < size; i++) {
		if (val[i] != s.val[i])
			return false;
	}
	return true;
}
const bool String::operator!=(const String& s) const{
	return !(*this == s);
}
const bool String::operator==(const char* s) const {
	if (s == nullptr && this->val == nullptr)
		return true;
	if (s == nullptr)
		return false;
	int i = 0;
	while (s[i] != '\0' && i < this->size) {
		if (s[i] != val[i])
			return false;
		i++;
	}
	if (this->size > i+1)
		return false;
	return true;
}
const bool String::operator!=(const char* s) const {
	return !(*this == s);
}
String String::operator+(const char s){
	String result = *this;
	addMemory(result.val, this->size, this->size + 1);
	result.size++;
	result.val[result.size - 2] = s;
	return result;
}