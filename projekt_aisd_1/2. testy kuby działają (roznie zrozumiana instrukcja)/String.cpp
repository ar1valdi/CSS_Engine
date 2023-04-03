#include "String.h"
#include <iostream>
#define stringBuf 32

int String::newStrings = 0;
String::String() {
	newStrings++;
	val = new char[stringBuf];
	*val = '\0';
	size = 1;
	bufs = 1;
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
	if(newSize < size)
		t[newSize - 1] = '\0';
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
		ch = getc(stdin);
		if (ch == '\n' || ch == EOF)
			ch = 0;

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

	if (size <= 0) {
		size = 1;
		if(val != nullptr)
			delete[]val;
		val = new char[stringBuf];
		*val = 0;
	}
	else {
		char* buf = val;

		while (stringBuf * bufs >= size)
			bufs--;
		bufs++;

		val = new char[bufs * stringBuf];
		for (int i = 0; i < size; i++)
			val[i] = buf[i];
		delete[] buf;
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
	newStrings++;
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = other;
}
String::String(String&& other) {
	newStrings++;
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = std::move(other);
}
String::String(const char*&& other) {
	newStrings++;
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = other;
}
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
	if (s_size > bufs * stringBuf) {
		while (bufs * stringBuf < s_size)
			bufs++;
		cleanVal();
		this->val = new char[bufs*stringBuf];
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
	if (s.bufs > this->bufs) {
		cleanVal();
		this->val = new char[s.bufs * stringBuf];
	}
	this->size = s.size;
	this->bufs = s.bufs;
	for (int i = 0; i < size; i++)
		val[i] = s.val[i];
	return *this;
}
String& String::operator=(char*&& s) {
	if (s == nullptr) {
		String empty;
		if (val != nullptr)
			delete[]val;
		*this = empty;
		return empty;
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