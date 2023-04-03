#pragma once
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
	int toErase = 0;

	while (isspace(s[toErase]))
		toErase++;

	s.erase(0, toErase);

	int id = s.getSize() - 2;
	if (id < 0)
		return;

	toErase = 0;
	while (isspace(s[id])) {
		toErase++;
		id--;
	}
	s.erase(id+1, toErase);
}
void readingSelectors(char& in, char& mode, Blok& nowyBlok, String& thing) {
	if (in == '{') {					// end of selectors
		mode = attributes;
		deleteFirstLastSpaces(thing);
		nowyBlok.selektory.add(thing);
		thing.clear();
		return;
	}
	if (in == ',')						// save selector and clear string for next one
	{
		deleteFirstLastSpaces(thing);
		nowyBlok.selektory.add(thing);
		thing.clear();
		return;
	}
	thing += in;
}
void readingAttr(char& in, char& mode, Blok& nowyBlok, String& thing, List2W& bloki, String& atr) {
	if (in == ':') {					// switching to values condiction
		mode = values;

		deleteFirstLastSpaces(thing);
		int id = nowyBlok.atrybuty.find(thing);	// delete prev occurance of given attr
		if (id != -1)
			nowyBlok.atrybuty.del(id);
		atr = thing;
		thing.clear();
		return;
	}
	if (in == '}') {
		mode = selectors;
		if(nowyBlok.atrybuty.getSize() != 0)
			bloki.add(nowyBlok);
		nowyBlok.clear();
		return;
	}
	thing += in;
}
void readingVals(char& in, char& mode, Blok& nowyBlok, String& thing, List2W& bloki, String& atr) {
	if (in == ';' || in == '}') {		// user has finished entering value
		deleteFirstLastSpaces(thing);
		nowyBlok.atrybuty.add(atr, thing);
		if (in == '}') {
			mode = selectors;
			if (nowyBlok.atrybuty.getSize() != 0)
				bloki.add(nowyBlok);
			nowyBlok.clear();
		}
		else
			mode = attributes;
		thing.clear();
		atr.clear();
		return;
	}
	thing += in;
}
void commandStartCheck(String& buf, char& in, char& mode, bool q=start) {
	buf += in;
	if (q == start) {
		while (1) {
			in = (char)getchar();
			buf += in;
			if (buf == "????\n")
			{
				mode = q == start ? commands : selectors;
				buf.clear();
				break;
			}
			if (buf.getSize() > 5 && buf != "????")
				break;
		}
	}
	else {
		while (1) {
			in = (char)getchar();
			buf += in;
			if (buf == "****\n")
			{
				mode = q == start ? commands : selectors;
				buf.clear();
				break;
			}
			if (buf.getSize() > 5 && buf != "****")
				break;
		}
	}
	
}
bool clBuf(bool& bufCleared) {
	char c = (char)getchar();
	while (c != '\n') {
		if (c == EOF)
			return 0;
		c = (char)getchar();
	}
	bufCleared = 1;
	return 1;
}
bool commandHandle(char& in, List2W& bloki, char& mode, String& secPartIn) {
	bool bufCleared = 0;

	if (in == '?') {
		in = (char)getchar();
		if (in != '\n' && in != EOF) {			//if command is something like ???? or ?h1?h2?


			if (!clBuf(bufCleared))
				return 0;
		}
		else {
			bufCleared = 1;
			if (bloki.getSize() == 1)
				int x = 0;
			cout << "? == " << bloki.getSize() << '\n';
		}

		// cuz of additional getc it requires special check for EOF
		// normally it is checked in bfClr() or .getline() function
		if (in == EOF)
			return 0;

	}
	else if (in >= '1' && in <= '9') {

		// getting input and assigning it to id variable

		int id = in - '0';
		in = (char)getchar();		// next char or ','
		while (in != ',') {			// load whole numeber, not just 1-9
			id = id * 10 + (in - '0');
			in = (char)getchar();
		}
		id -= 1;

		if (id < 0 || id >= bloki.getSize())		// ignore if id is incorrect
			in = 0;		// by assigning 0 to in, program wont enter any case in switch
		else
			in = (char)getchar();		// get further option


		switch (in) {

		// delete things

		case 'D':
			in = (char)getchar();

			secPartIn.getline();
			bufCleared = 1;

			if (secPartIn[0] == '*')	// everything
			{
				if (bloki.del(id))
					cout << id + 1 << ",D,* == deleted\n";
			}
			else {									// only one attr
				Blok* blokID = &bloki[id];
				int idToD = blokID->atrybuty.find(secPartIn);

				if (blokID->atrybuty.del(idToD)) {
					if (blokID->atrybuty.getSize() == 0)
						bloki.del(id);
					cout << id+1 << ",D," << secPartIn << " == deleted\n";
				}
			}
			break;

		// operations with selectors

		case 'S':
			in = (char)getchar();
			in = (char)getchar();
			if (in == '?') 					// show number of selectors
			{
				cout << id + 1 << ",S,? == " << bloki[id].selektory.getSize() << '\n';
				if (!clBuf(bufCleared))
					return 0;
				if (id == 14)
					int x = 4;
			}
			else {								// show selector of j-1 id
				int j = 0;
				while (in != '\n') {
					j = j * 10 + (in - '0');
					in = (char)getchar();
				}
				j -= 1;
				Blok* blokID = &bloki[id];
				if (j >= 0 && j < blokID->selektory.getSize())
					cout << id+1 << ",S," << j+1 << " == " << blokID->selektory[j] << '\n';
			}
			break;

		// operations with attributes

		case 'A':
			in = (char)getchar();
			//in = (char)getchar();

			secPartIn.getline();
			bufCleared = 1;

			if (secPartIn[0] == '?' && (secPartIn[1] == '\0' || secPartIn[1] == '\n'))					// show number of attributes
				cout << id + 1 << ",A,? == " << bloki[id].atrybuty.getSize() << '\n';

			else {							// show value for n attribute
				NodeAtr* returned = &bloki[id].atrybuty.find(secPartIn, 1);
				if(!returned->isEmpty())
				cout << id + 1 << ",A," << secPartIn << " == " << returned->getValV() << '\n';
			}

			break;
		}
	}
	else if (in != '0' && in != '\n') {
		String z;
		while (in != ',') {
			z += in;
			in = (char)getchar();

			if (in == '\n')
				break;
		}		
		in = (char)getchar();
		int num = 0;
		switch (in) {
		case 'S':		// number of selector z instances in list
			num = bloki.instancesOfSel(z);

			if (num != -1)
				cout << z << ",S,? == " << num << '\n';

			if (!clBuf(bufCleared))
				return 0;
			break;
		case 'A':		// number of attribute z instances
			
			num = bloki.instancesOfAtr(z);

			if (num != -1)
				cout << z << ",A,? == " << num << '\n';
			
			if (!clBuf(bufCleared))
				return 0;
			break;
		case 'E':		// last value of atr (2nd string) for z selector

			in = (char)getchar();	//burn ','
			secPartIn.getline();
			bufCleared = 1;

			String returned = bloki.lastOccOfAtr(z, secPartIn);
			if (returned.getSize() != 0)
				cout << z << ",E," << secPartIn << " == " << returned << '\n';

			break;
		}
	}
	
	if (in != '\n' && !bufCleared)
		if (!clBuf(bufCleared)) return 0;

	if (String::getEOFdetection())
		return 0;

	return 1;
}

int main()
{
	List2W bloki;
	Blok nowyBlok;
	char mode = selectors;

	bool getFromBuf = false;
	String thing, buf, atr, secPartIn;
	thing = buf = "";
	char in;

	while (1) {
		if (buf.getSize() == 1)					// read input (1 cuz empty has '\0'
		{
			in = (char)getchar();
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
			if (!commandHandle(in, bloki, mode, secPartIn)) {
				return 0;
			}
			break;
		}
	}
}