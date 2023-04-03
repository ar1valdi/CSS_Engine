#pragma once
using namespace std;
#include "List2W.h"
#include "String.h"
#include "operatory.h"
#include <cctype>

#define selectors 1
#define attributes 2
#define values 3
#define commands 4

#define start 1
#define end 0

void deleteFirstLastSpaces(String& s) {
	while (isspace(s[0])) {
		s.erase(0, 1);
	}
	int id = s.getSize() - 2;
	if (id < 0)
		return;
	while (isspace(s[id])) {
		s.erase(id, 1);
		id--;
	}
}

// selektor "" oznacza że jest aplikowane do wszystkiego

void readingSelectors(char& in, char& mode, Blok& nowyBlok, String& thing) {
	if (in == '{') {					// koniec wczytywania selektorów
		mode = attributes;
		deleteFirstLastSpaces(thing);
		nowyBlok.selektory.add(thing);
		thing = "";
		return;
	}
	if (in == ',')						// zmiana na następny selektor
	{
		deleteFirstLastSpaces(thing);
		nowyBlok.selektory.add(thing);
		thing = "";
		return;
	}
	thing = thing + in;
}

void readingAttr(char& in, char& mode, Blok& nowyBlok, String& thing, List2W& bloki) {
	Blok emptyBlok;
	if (in == ':') {					// conduction on switching to values
		mode = values;

		deleteFirstLastSpaces(thing);
		int id = nowyBlok.atrybuty.find(thing);	// delete prev occurance of given attr
		if (id != -1) {
			nowyBlok.atrybuty.del(id);
			nowyBlok.wartosci.del(id);
		}
		nowyBlok.atrybuty.add(thing);
		thing = "";
		return;
	}
	if (in == '}') {
		mode = selectors;
		bloki.add(nowyBlok);
		nowyBlok = emptyBlok;
		return;
	}
	thing = thing + in;
}

void readingVals(char& in, char& mode, Blok& nowyBlok, String& thing, List2W& bloki) {
	Blok emptyBlok;
	if (in == ';' || in == '}') {		// koniec wczytywania wartosci
		deleteFirstLastSpaces(thing);
		nowyBlok.wartosci.add(thing);
		if (in == '}') {
			mode = selectors;
			bloki.add(nowyBlok);
			nowyBlok = emptyBlok;
		}
		else
			mode = attributes;
		thing = "";
		return;
	}
	thing = thing + in;
}

void commandStartCheck(String& buf, char& in, char& mode, bool q=start) {
	buf = buf + in;
	String reg;
	reg = q == start ? "????" : "****";
	while (1) {
		in = getc(stdin);
		buf = buf + in;
		if (buf == reg + '\n')
		{
			mode = q == start ? commands : selectors;
			//if (mode == selectors)
			//	cout << "entering selectors\n";
			//else
			//	cout << "entering commands\n";
			buf = "";
			break;
		}
		if (buf.getSize() > reg.getSize() && buf != reg)
			break;
	}
}

void clBuf() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool commandHandle(char& in, List2W& bloki, char& mode) {
	if (in == 'p') {
		for (int i = 0; i < bloki.getSize(); i++)
			cout << i + 1 << ":\n" << bloki[i] << endl;
		clBuf();
	}
	else 
	if (in == '?') {
		cout << "? == " << bloki.getSize() << endl;
		clBuf();
	}
	else if (in >= '1' && in <= '9') {

		// getting input and assigning it to id variable

		int id = in - '0';
		in = getc(stdin);		// next char or ','
		while (in != ',') {			// load whole numeber, not just 1-9
			id = id * 10 + (in - '0');
			in = getc(stdin);
		}
		id -= 1;

		if (id < 0 || id >= bloki.getSize())		// ignore if id is incorrect
			in = 0;		// by assigning 0 to in, program wont enter any case in switch
		else
			in = getc(stdin);		// get further option

		switch (in) {

		// delete things

		case 'D':
			if (bloki.getSize() == 55)
				int x = 0;
			in = getc(stdin);
			in = getc(stdin);
			if (in == '*' && bloki.del(id))	// everything
			{
				cout << id + 1 << ",D,* == deleted\n";
				clBuf();
			}
			else {									// only one attr
				String n;
				n.getline();
				n = in + n;
				int idToD = bloki[id].atrybuty.find(n);
				if (bloki[id].atrybuty.del(idToD) && bloki[id].wartosci.del(idToD)) {
					if (bloki[id].atrybuty.getSize() == 0)
						bloki.del(id);
					cout << id+1 << ",D," << n << " == deleted\n";
				}
			}
			break;

		// operations with selectors

		case 'S':
			in = getc(stdin);
			in = getc(stdin);
			if (in == '?') 					// show number of selectors
			{
				cout << id + 1 << ",S,? == " << bloki[id].selektory.getSize() << endl;
				clBuf();
			}
			else {								// show selector of j-1 id
				int j = 0;
				while (in != '\n') {
					j = j * 10 + (in - '0');
					in = getc(stdin);
				}
				j -= 1;
				if (j >= 0 && j < bloki[id].selektory.getSize())
					cout << id+1 << ",S," << j+1 << " == " << bloki[id].selektory[j] << endl;
			}
			break;

		// operations with attributes

		case 'A':
			in = getc(stdin);
			in = getc(stdin);
			if (in == '?')					// show number of attributes
			{
				cout << id + 1 << ",A,? == " << bloki[id].atrybuty.getSize() << endl;
				clBuf();
			}
			else {
				String n;
				n.getline();
				n = in + n;
				int idToShow = bloki[id].atrybuty.find(n);
				if (idToShow != -1)
					cout << id+1 << ",A," << n << " == " << bloki[id].wartosci[idToShow] << '\n';
			}
			break;
		}
	}
	else if (in != '0' && in != '\n') {
		String z;
		while (in != ',') {
			z = z + in;
			in = getc(stdin);
		}		
		in = getc(stdin);
		int num = 0;
		switch (in) {
		case 'S':
			for (int i = 0; i < bloki.getSize(); i++) {
				if (bloki[i].selektory.find(z) != -1)
					num++;
			}
			cout << z << ",S,? == " << num << '\n';
			clBuf();
			break;
		case 'A':
			for (int i = 0; i < bloki.getSize(); i++) {
				if (bloki[i].atrybuty.find(z) != -1)
					num++;
			}
			cout << z << ",A,? == " << num << '\n';
			clBuf();
			break;
		case 'E':
			String atr, val;
			in = getc(stdin);	//burn ','
			atr.getline();
			for (int i = 0; i < bloki.getSize(); i++) {
				if (bloki[i].selektory.find(z) != -1 || 
					(bloki[i].selektory.getSize() == 1 && bloki[i].selektory[0].getVal() == "")) {
					int id = bloki[i].atrybuty.find(atr);
					if(id != -1)
						val = bloki[i].wartosci[id].getVal();
				}
			}
			if(val != "")
				cout << z << ",E," << atr << " == " << val << endl;
			break;
		}
	}
	else if (in != '\n')
		clBuf();

	// burn leftovers from input (mostly from incorrect commands)
	//if (cin.rdbuf()->in_avail() > 0) {
	//	cout << cin.rdbuf()->in_avail() << " - ";

	/*
	if (cin.peek() != EOF && cin.peek() != '\n') {
		cout << cin.peek() << " ='" <<(char)cin.peek() << "'\n";
		do {
			in = getc(stdin);
			if (in == '*')
				cout << "w burn: in='" << in << "'   mode='" << mode << "'\n";
		} while (in != '\n' && in!= '\0' && in != EOF);
	}*/

	if (in == '\0' || in == EOF)
		return 0;
	return 1;
}

void main2() {
	char in = getc(stdin);
	cout << in;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (1) {
		in = getc(stdin);
		cout << in;
	}
}

int main()
{
	List2W bloki;
	Blok nowyBlok;
	char mode = selectors;

	bool getFromBuf = false;
	String thing, buf;
	thing = buf = "";
	char in;

	while (1) {
		if (buf == "")										// read input
		{
			in = getc(stdin);
			if (mode!= commands && in == '\n')
				continue;
			getFromBuf = 0;
		}
		else {												// read from buffer
			getFromBuf = 1;
			in = buf[0];
			buf.erase(0, 1);
		}

		// change mode command detection
		if (!getFromBuf) {
			if (in == '?' && mode != commands) {
				commandStartCheck(buf, in, mode);
				continue;
			}
			else if (in == '*' && mode == commands) {
				commandStartCheck(buf, in, mode, end);
				continue;
			}
		}

		// end of program detection
		if (in == 0 || in == EOF)
			break;

		// engine itself
		switch (mode) {
		case selectors:
			readingSelectors(in, mode, nowyBlok, thing);
			break;
		case attributes:
			readingAttr(in, mode, nowyBlok, thing, bloki);
			break;
		case values:
			readingVals(in, mode, nowyBlok, thing, bloki);
			break;
		case commands:
			if (!commandHandle(in, bloki, mode))
				return 0;
			break;
		}
	}
}