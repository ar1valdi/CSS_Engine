#pragma once
using namespace std;
#include "List2W.h"
#include "String.h"
#include "operatory.h"

#define selectors 1
#define attributes 2
#define values 3
#define commands 4

void deleteLastSpaces(String& s) {
	int id = s.getSize() - 1;
	while (s[id] == ' ') {
		s.erase(id, 1);
		id--;
	}
}

// selektor "" oznacza że jest aplikowane do wszystkiego

int main()
{
	int id, prevId;
	String input, wynik;
	bool modeChange = 0;

	List2W bloki;
	Blok nowyBlok, emptyBlok;
	char mode = selectors;

	bool bylZnak = false;
	bool getFromBuf = false;
	String thing, buf, inC;
	thing = buf = "";
	char in = ' ';

	while (1) {
		if (buf == "")							// wczytanie wejścia
		{
			if (mode != commands) {
				in = getc(stdin);
				if (in == '\n')
					continue;
			}
			else
				inC.getline();
			getFromBuf = 0;
		}
		else {
			getFromBuf = 1;
			in = buf[0];
			buf.erase(0, 1);
		}

		if (in == '?' && !getFromBuf) {						// detekcja "????" na wejsciu in

			buf = buf + in; 
			while (1) {
				in = getc(stdin);
				buf = buf + in;
				if (buf == "????\n")
				{
					mode = commands;
					buf = "";
					break;
				}
				if (buf.getSize() > 5 && buf != "????")
					break;
			}
			continue;
		}

		if (in == 0 || in == EOF)
			break;

		switch (mode) {
		case selectors:
			if (in == '{') {		// koniec wczytywania selektorów
				mode = attributes;
				nowyBlok.selektory.add(thing);
				thing = "";
				break;
			}
			if (in == ',')						// zmiana na następny selektor
			{
				nowyBlok.selektory.add(thing);
				thing = "";
				break;
			}
			if (in == ' ')						// usuwanie spacji
				break;
			thing = thing + in;					// dopisywanie znaku do selektora
			break;
		case attributes:
			if (in == ':') {					// warunek przejscia do atrybutow
				mode = values;
				nowyBlok.atrybuty.add(thing);
				thing = "";
				break;
			}
			if (in == '}') {
				bloki.add(nowyBlok);
				nowyBlok = emptyBlok;
				break;
			}
			if (in == ' ')						// usuwanie spacji
				break;
			thing = thing + in;
			break;
		case values:
			if (in == ';' || in == '}') {		// koniec wczytywania wartosci
				deleteLastSpaces(thing);
				nowyBlok.wartosci.add(thing);
				if (in == '}') {
					mode = selectors;
					bloki.add(nowyBlok);
					nowyBlok = emptyBlok;
				}
				else
					mode = attributes;
				thing = "";
				bylZnak = 0;
				break;
			}
			if (!bylZnak && in == ' ')			// usuwanie spacji przed wartoscia
				break;
			thing = thing + in;
			bylZnak = 1;
			break;
		case commands:
			if (inC == "print") {
				for (int i = 0; i < bloki.getSize(); i++)
					cout << i+1 << ":\n" << bloki[i] << endl;
			}
			else if (inC == "****")
				mode = selectors;
			break;
		}
	}
}