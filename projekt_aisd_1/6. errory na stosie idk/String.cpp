#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <iostream>
using namespace std;
#define stringBuf 512

int cmd, al;

bool String::EOFdetected = 0;
bool String::DEBUG_FLAG = 0;
String::String() {
	val = nullptr;
	size = 0;
	bufs = 0;
}
char* String::getVal() const {
	return this->val;
}
void addMemory(char*& t, int &size, int newSize) {
	char* buf = move(t);
	t = new char[newSize];

	//przepisuje tablice
	for (int i = 0; i < size - 1 && i < newSize; i++)
		t[i] = buf[i];
	t[newSize - 1] = '\0';

	if (size == 0 && newSize > 0) {
		size++;
		t[0] = '\0';
	}

	if (buf != nullptr)
		delete[] buf;
}
bool String::getEOFdetection() {
	return String::EOFdetected;
}
void String::getline() {
	if (bufs != 1) {
		cleanVal();
		this->val = new char[stringBuf];
		bufs = 1;
	}
	size = 0;
	int ch = EOF;
	while (ch) {
		ch = (char)getchar();
		if (ch == '\n')
			ch = 0;
		else if (ch == EOF) {
			ch = 0;
			String::EOFdetected = 1;
		}

		if (size < stringBuf * bufs)
			val[size++] = ch;
		else {
			bufs++;
			addMemory(this->val, size, bufs * stringBuf);
			val[size++] = ch;
		}
	}
}
void String::cleanVal() {
	if (this->val != nullptr) {
		delete[] this->val;
		this->val = nullptr;
	}
}
int String::find(char c, int start) const {
	char* pos = strchr(val + start, c);
	if (pos == NULL)
		return -1;
	else
		return int(pos - val);
}
void String::erase(int start, int n) {
	if (n == 0)
		return;
	int id = start;
	for (int i = start; i+n < this->size; i++) {
		val[i] = val[i + n];
	}
	size -= n;

	if (size <= 0) {
		size = 0;
		bufs = 0;
		cleanVal();
	}
	else {
		int oldBufs = bufs;
		while (stringBuf * bufs >= size)
			bufs--;
		bufs++;
		if (oldBufs != bufs) {
			char* buf = move(val);

			val = new char[bufs * stringBuf];
			strcpy(val, buf);
			delete[] buf;
		}
	}
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
	this->bufs = 0;
	*this = other;
}
String::String(String&& other) {
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = move(other);
}
String::String(const char*&& other) {
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = other;
}
char& String::operator[](int i) {
	return this->val[i];
}
void String::clear() {
	if (bufs > 1) {
		delete[] this->val;
		this->val = new char[stringBuf];
		bufs = 1;
	}
	size = 1;
	val[0]='\0';
}
String& String::operator=(const char* s) {
	if (s == nullptr) {
		cleanVal();
		size = 0;
		bufs = 0;
		return *this;
	}
	int i = 0;
	int s_size = strlen(s) + 1;		// +1 cuz of '\0' at the end
	if (s_size > bufs * stringBuf) {
		while (bufs * stringBuf < s_size)
			bufs++;
		cleanVal();
		this->val = new char[bufs*stringBuf];
	}
	strcpy(val, s);
	this->val[s_size - 1] = 0;
	this->size = s_size;
	return *this;
}
String& String::operator=(const String& s) {
	if (s.bufs != this->bufs) {
		cleanVal();
		this->val = new char[s.bufs * stringBuf];
		this->bufs = s.bufs;
	}
	this->size = s.size;
	strcpy(val, s.val);
	return *this;
}
String& String::operator=(char*&& s) {
	if (s == nullptr) {
		cleanVal();
		size = 0;
		bufs = 0;
		return *this;
	}
	std::swap(this->val, s);
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
	this->bufs = s.bufs;
	std::swap(this->val, s.val);
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
/*String String::operator+(const char s) {
	String result = *this;
	addMemory(result.val, this->size, this->size + 1);
	result.size++;
	result.val[result.size - 2] = s;
	return result;
}*/
String& String::operator+=(const char s) {
	if (this->size + 1 > stringBuf * bufs)
		addMemory(this->val, this->size, stringBuf * (++bufs));
	this->size++;
	val[size - 2] = s;
	val[size - 1] = 0;
	return *this;
}