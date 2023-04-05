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
			in = getchar();
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
			in = getchar();
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
	char c = getchar();
	while (c != '\n') {
		if (c == EOF)
			return 0;
		c = getchar();
	}
	bufCleared = 1;
	return 1;
}
void readWholeNumber(int& id, char& in) {
	in = getchar();		// next char or ','
	while (in != ',') {			// load whole numeber, not just 1-9
		id = id * 10 + (in - '0');
		in = getchar();
	}
	id -= 1;
}
void deleteOneAttr(const int& id, List2W& bloki, String& secPartIn) {
	Blok* blokID = &bloki[id];
	int idToD = blokID->atrybuty.find(secPartIn);

	if (blokID->atrybuty.del(idToD)) {
		if (blokID->atrybuty.getSize() == 0)
			bloki.del(id);
		cout << id + 1 << ",D," << secPartIn << " == deleted\n";
	}
}
bool showNumberOfSelectors(const int& id, List2W& bloki, bool& bufCleared) {
	cout << id + 1 << ",S,? == " << bloki[id].selektory.getSize() << '\n';
	if (!clBuf(bufCleared))
		return 0;
	return 1;
}
bool printSectionsNumber(char& in, List2W& bloki, char& mode, String& secPartIn, bool& bufCleared) {
	in = getchar();
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

	// cuz of additional getchar() it requires special check for EOF
	// normally it is checked in bfClr() or .getline() method
	if (in == EOF)
		return 0;

	return 1;
}
void deleteSection(List2W& bloki, int id) {
	if (bloki.del(id))
		cout << id + 1 << ",D,* == deleted\n";
}
void showSelectorWithID(char& in, List2W& bloki, int id) {
	int j = 0;
	while (in != '\n') {
		j = j * 10 + (in - '0');
		in = getchar();
	}
	j -= 1;
	Blok* blokID = &bloki[id];
	if (j >= 0 && j < blokID->selektory.getSize()) {
		cout << id + 1 << ",S," << j + 1 << " == " << blokID->selektory[j] << '\n';
	}
}
void showValueOfAttributeWithID(const int& id, List2W& bloki, String& secPartIn) {
	NodeAtr* returned = &bloki[id].atrybuty.find(secPartIn, 1);
	if (!(returned->isEmpty())) {
		cout << id + 1 << ",A," << secPartIn << " == " << returned->getValV() << '\n';
	}
}
bool numOfSelectorInstancesInList(int& num, List2W& bloki, const String& z, bool& bufCleared) {
	num = bloki.instancesOfSel(z);

	if (num != -1)
		cout << z << ",S,? == " << num << '\n';

	if (!clBuf(bufCleared))
		return 0;
	return 1;
}
bool numOfAttributeInstancesInList(int& num, List2W& bloki, const String& z, bool& bufCleared) {
	num = bloki.instancesOfAtr(z);

	if (num != -1) {
		cout << z << ",A,? == " << num << '\n';
	}
	if (!clBuf(bufCleared))
		return 0;
	return 1;
}
void lastValueOfAttribute(String& secPartIn, bool& bufCleared, List2W& bloki, const String& z) {
	secPartIn.getline();
	bufCleared = 1;

	String returned = bloki.lastOccOfAtr(z, secPartIn);
	if (returned.getSize() != 0) {
		cout << z << ",E," << secPartIn << " == " << returned << '\n';
	}
}

bool commandHandle(char& in, List2W& bloki, char& mode, String& secPartIn) {
	bool bufCleared = 0;
	if (in == '?') {
		if (!printSectionsNumber(in, bloki, mode, secPartIn, bufCleared))
			return 0;
	}
	else if (in >= '1' && in <= '9') {

		// read id
		int id = in - '0';
		readWholeNumber(id, in);	

		// ignore if id is incorrect. by assigning 0 to in, 
		// program wont enter any case in switch, otherwise 
		// get further option
		if (id < 0 || id >= bloki.getSize())
			in = 0;
		else
			in = getchar();

		switch (in) {

		// delete things

		case 'D':
			in = getchar();	//burn ','

			secPartIn.getline();
			bufCleared = 1;

			if (secPartIn[0] == '*')
			{
				if (id == 0)
					int x = 0;
				deleteSection(bloki, id);
			}
			else {
				deleteOneAttr(id, bloki, secPartIn);
			}
			break;

		// operations with selectors

		case 'S':
			in = getchar();	// burn ','
			in = getchar();	// check if command is right
			if (in == '?')
			{
				if (!showNumberOfSelectors(id, bloki, bufCleared))
					return 0;
			}
			else {
				showSelectorWithID(in, bloki, id);
			}
			break;

		// operations with attributes

		case 'A':
			in = getchar();	// burn ','

			secPartIn.getline();
			bufCleared = 1;

			// show number of attributes
			if (secPartIn[0] == '?' && (secPartIn[1] == '\0' || secPartIn[1] == '\n')) {				
				cout << id + 1 << ",A,? == " << bloki[id].atrybuty.getSize() << '\n';
			}

			else {
				showValueOfAttributeWithID(id, bloki, secPartIn);
			}
			
			break;
		}
	}
	else if (in != '0' && !isspace(in)) {

		// get rest of the word
		String z;
		while (in != ',') {
			z += in;
			in = getchar();

			if (in == '\n')
				break;
		}	

		// get further option
		in = getchar();
		int num = 0;

		switch (in) {
		case 'S':

			if (!numOfSelectorInstancesInList(num, bloki, z, bufCleared))
				return 0;

			break;
		case 'A':
			
			if (!numOfAttributeInstancesInList(num, bloki, z, bufCleared))
				return 0;
			
			break;
		case 'E':

			in = getchar();	//burn ','
			lastValueOfAttribute(secPartIn, bufCleared, bloki, z);

			break;
		}
	}
	
	// clear any remainings in stream buff
	if (in != '\n' && !bufCleared)
		if (!clBuf(bufCleared)) 
			return 0;

	// check if there was EOF detected in getline() method
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
		// read input (1 cuz empty string has '\0')
		if (buf.getSize() == 1)					
		{
			in = getchar();
			if (mode!= commands && in == '\n')
				continue;
			getFromBuf = 0;
		}
		// read from buffer (created when checking for '????' pr '****')
		else {												
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

		// quit program detection
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

	// every variable that was created 
	// statically is deleted automatically
}