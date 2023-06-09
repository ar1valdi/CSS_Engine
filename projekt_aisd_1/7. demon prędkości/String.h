#pragma once
#include <iostream>

class String {
private:
	char* val;
	int size, bufs;
	void cleanVal();
	static bool EOFdetected;
	friend String operator+(const char c, const String& s);
	friend class ListAtr;
	friend class List;
public:
	static bool getEOFdetection();
	String();
	String(const String& other);
	//String(const char*& other);
	String(const char*&& other);
	String(String&& other);
	char* getVal() const;
	void getline();
	int getSize() const;
	int find(char c, int start=0) const;
	void erase(int start, int n);
	void clear();
	String& operator=(const char* s);
	String& operator=(char*&& s);
	String& operator=(const String& s);
	String& operator=(String&& s);
	const bool operator==(const String& s) const;
	const bool operator!=(const String& s) const;
	const bool operator==(const char* s) const;
	const bool operator!=(const char* s) const;
	String& operator+=(const char s);
	char& operator[](int i);
	~String();
};