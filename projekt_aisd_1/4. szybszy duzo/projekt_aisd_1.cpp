﻿#pragma once
using namespace std;
#include "List2W.h"
#include "String.h"
#include "operatory.h"
#include <stdio.h>

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
	if (in == '{') {					// end of selectors
		mode = attributes;
		deleteFirstLastSpaces(thing);
		nowyBlok.selektory.add(thing);
		thing = "";
		return;
	}
	if (in == ',')						// save selector and clear string for next one
	{
		deleteFirstLastSpaces(thing);
		nowyBlok.selektory.add(thing);
		thing = "";
		return;
	}
	thing += in;
}

void readingAttr(char& in, char& mode, Blok& nowyBlok, String& thing, List2W& bloki, String& atr) {
	Blok emptyBlok;
	if (in == ':') {					// switching to values condiction
		mode = values;

		deleteFirstLastSpaces(thing);
		int id = nowyBlok.atrybuty.find(thing);	// delete prev occurance of given attr
		if (id != -1)
			nowyBlok.atrybuty.del(id);
		atr = thing;
		thing = "";
		return;
	}
	if (in == '}') {
		mode = selectors;
		bloki.add(nowyBlok);
		nowyBlok = emptyBlok;
		return;
	}
	thing += in;
}

void readingVals(char& in, char& mode, Blok& nowyBlok, String& thing, List2W& bloki, String& atr) {
	Blok emptyBlok;
	if (in == ';' || in == '}') {		// user has finished entering value
		deleteFirstLastSpaces(thing);
		nowyBlok.atrybuty.add(atr, thing);
		if (in == '}') {
			mode = selectors;
			bloki.add(nowyBlok);
			nowyBlok = emptyBlok;
		}
		else
			mode = attributes;
		thing = atr = "";
		return;
	}
	thing += in;
}

void commandStartCheck(String& buf, char& in, char& mode, bool q=start) {
	buf += in;
	if (q == start) {
		while (1) {
			in = getc(stdin);
			buf += in;
			if (buf == "????\n")
			{
				mode = q == start ? commands : selectors;
				//if (mode == selectors)
				//	cout << "entering selectors\n";
				//else
				//	cout << "entering commands\n";
				buf = "";
				break;
			}
			if (buf.getSize() > 5 && buf != "????")
				break;
		}
	}
	else {
		while (1) {
			in = getc(stdin);
			buf += in;
			if (buf == "****\n")
			{
				mode = q == start ? commands : selectors;
				//if (mode == selectors)
				//	cout << "entering selectors\n";
				//else
				//	cout << "entering commands\n";
				buf = "";
				break;
			}
			if (buf.getSize() > 5 && buf != "****")
				break;
		}
	}
	
}

void clBuf(bool& bufCleared) {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	bufCleared = 1;
}

bool commandHandle(char& in, List2W& bloki, char& mode) {
	bool bufCleared = 0;
	//if (in == 'p') {
	//	for (int i = 0; i < bloki.getSize(); i++)
	//		cout << i + 1 << ":\n" << bloki[i] << '\n';
	//	clBuf();+
	//}
	//else 
	if (in == '?') {
		in = getc(stdin);
		if (in != '\n') {				//if command is something like ???? or ?h1?h2?
			clBuf(bufCleared);
		}
		else {
			if (bloki.getSize() == 1304)
				int x = 0;
			bufCleared = 1;
			cout << "? == " << bloki.getSize() << '\n';
		}
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
			in = getc(stdin);
			in = getc(stdin);
			if (in == '*')
				int x = 0;
			if (in == '*' && bloki.del(id))	// everything
			{
				cout << id + 1 << ",D,* == deleted\n";
				clBuf(bufCleared);
			}
			else {									// only one attr
				String n;

				n.getline();
				bufCleared = 1;
				n = in + n;							//first letter is in in var

				int idToD = bloki[id].atrybuty.find(n);

				if (bloki[id].atrybuty.del(idToD)) {
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
				cout << id + 1 << ",S,? == " << bloki[id].selektory.getSize() << '\n';
				clBuf(bufCleared);
			}
			else {								// show selector of j-1 id
				int j = 0;
				while (in != '\n') {
					j = j * 10 + (in - '0');
					in = getc(stdin);
				}
				j -= 1;
				if (j >= 0 && j < bloki[id].selektory.getSize())
					cout << id+1 << ",S," << j+1 << " == " << bloki[id].selektory[j] << '\n';
			}
			break;

		// operations with attributes

		case 'A':
			in = getc(stdin);
			in = getc(stdin);
			if (in == '?')					// show number of attributes
			{
				cout << id + 1 << ",A,? == " << bloki[id].atrybuty.getSize() << '\n';
				clBuf(bufCleared);
			}
			else {							// show value for n attribute
				String n;
				n.getline();
				bufCleared = 1;
				n = in + n;
				try {
					String returned = bloki[id].atrybuty.find(n, 1).getValV();
					cout << id + 1 << ",A," << n << " == " << returned << '\n';
				}
				catch(runtime_error e){}
			}
			break;
		}
	}
	else if (in != '0' && in != '\n') {
		String z;
		while (in != ',') {
			z += in;
			in = getc(stdin);

			if (in == '\n')
				break;
		}		
		in = getc(stdin);
		int num = 0;
		switch (in) {
		case 'S':
			for (int i = 0; i < bloki.getSize(); i++) {
				if (bloki[i].selektory.find(z) != -1)
					num++;
				if (i == 225) {
					int x = 0;
				}
				if (0)
					int x = 0;
			}
			cout << z << ",S,? == " << num << '\n';
			clBuf(bufCleared);
			break;
		case 'A':
			for (int i = 0; i < bloki.getSize(); i++) {
				if (bloki[i].atrybuty.find(z) != -1)
					num++;
			}
			cout << z << ",A,? == " << num << '\n';
			clBuf(bufCleared);
			break;
		case 'E':
			
			/*
			String atr, val;
			in = getc(stdin);	//burn ','
			atr.getline();
			bufCleared = 1;
			for (int i = 0; i < bloki.getSize(); i++) {
				if (bloki[i].selektory.find(z) != -1 || 
					(bloki[i].selektory.getSize() == 1 && bloki[i].selektory[0].getVal() == "")) {
					int id = bloki[i].atrybuty.find(atr);
					if(id != -1)
						val = bloki[i].atrybuty[id].getValV();
				}
			}
			if(val != "")
				cout << z << ",E," << atr << " == " << val << '\n';
			break;
			*/

			
			String n;
			in = getc(stdin);	//burn ','
			n.getline();
			bufCleared = 1;

			//try {
				String returned =bloki.lastOccOfAtr(z, n);
				if(returned.getSize() != 0)
					cout << z << ",E," << n << " == " << returned << '\n';
			//}
			//catch (runtime_error e) {}

			break;
		}
	}
	
	
	if (in != '\n' && !bufCleared)
		clBuf(bufCleared);

	if (in == EOF)
		return 0;
	return 1;
}

int main()
{
	List2W bloki;
	Blok nowyBlok;
	char mode = selectors;

	bool getFromBuf = false;
	String thing, buf, atr;
	thing = buf = "";
	char in;

	while (1) {
		if (buf.getSize() == 1)							// read input (1 cuz empty has '\0'
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
		if (in == EOF)
			break;

		// engine itself
		switch (mode) {
		case selectors:
			readingSelectors(in, mode, nowyBlok, thing);
			break;
		case attributes:
			readingAttr(in, mode, nowyBlok, thing, bloki, atr);
			break;
		case values:
			readingVals(in, mode, nowyBlok, thing, bloki, atr);
			break;
		case commands:
			if (!commandHandle(in, bloki, mode)) {
				return 0;
			}
			break;
		}
	}
}