#include <FL/Fl.H>
#include <FL/Fl_Hold_Browser.H>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <map>
#include "Processing.h"
#include "word.h"

using namespace std;

map<string, word> loadWord(Fl_Hold_Browser* worddb) {

	map<string, word> dictionary;
	fstream f;
	string line;
	string key;
	word value;
	try {
		f.open("anhviet109K.index", ios::in);
		int cnt = 0;
		while (!f.eof()) {
			getline(f, line);
			key = line.substr(0, line.find('\t', 0));
			word test = dictionary[key];
			if (test.isNull()) {
				value.setBegin(line.substr(line.find('\t', 0) + 1, line.find('\t', line.find('\t', 0) + 1) - (key.length() + 1)));
				value.setLength(line.substr(key.length() + value.getBegin().length() + 2, line.length() - (key.length() + value.getBegin().length() + 2)));
				cnt++;
				value.setNum(cnt);
				worddb->add(key.c_str());
				_strlwr_s((char*)key.c_str(), key.length() + 1);
				dictionary[key] = value;
			}
		}
		f.close();
	}
	catch (exception e) {
	}

	return dictionary;

}

map<string, addWord> loadAddWord(Fl_Hold_Browser* worddb) {

	map<string, addWord> dictionary_add;
	fstream f;
	string line, key;
	addWord value;

	try {
		f.open("addword.dict", ios::in);
		int cnt = 103790;
		string text = "";
		while (!f.eof()) {
			getline(f, line);
			text += "\n" + line;
		}

		int pos = 0;
		while (text.find('@', pos + 1) != -1  && text.find('@', pos + 1) != 4294967295) {
			pos = text.find('@', pos + 1);
			key = text.substr(pos, text.find('\t', pos) - pos);
			key.replace(0, 1, "");
			if (text.find('@', pos + 1) != -1 && text.find('@', pos + 1) != 4294967295) {
				value.setMeaning(text.substr(text.find('\t', pos) + 1, text.find('@', pos + 1) - (text.find('\t', pos) + 1)));
			}
			else {
				value.setMeaning(text.substr(text.find('\t', pos) + 1, text.length() - (text.find('\t', pos) + 1)));
			}
			value.setName(key);
			cnt++;
			value.setNum(cnt);
			worddb->add(key.c_str());
			dictionary_add[key] = value;
		}
		f.close();

		for (int i = 0; i < 20; i++) {
			worddb->add(" ");
		}
	}
	catch (exception e) {

	}

	return dictionary_add;

}

map<string, int> loadHistory(Fl_Hold_Browser* worddb) {

	map<string, int> history;
	fstream f;
	string line;

	try {
		f.open("history.dict", ios::in);
		int cnt = 1;
		getline(f, line);
		while (!f.eof()) {
			getline(f, line);
			if (history[line] < 1 || history[line] > 31) {
				history[line] = cnt;
				cnt++;
				worddb->add(line.c_str());
			}
		}

		f.close();

		for (int i = 0; i < 35; i++) {
			worddb->add(" ");
		}
	}
	catch (exception e) {

	}

	return history;

}

map<string, int> loadFavorite(Fl_Hold_Browser* worddb) {

	map<string, int> favorite;
	fstream f;
	string line;

	try {
		f.open("favorite.dict", ios::in);
		int cnt = 1;
		getline(f, line);
		while (!f.eof()) {
			getline(f, line);
			favorite[line] = cnt;
			cnt++;
			worddb->add(line.c_str());
		}

		f.close();

		for (int i = 0; i < 30; i++) {
			worddb->add(" ");
		}
	}
	catch (exception e) {

	}

	return favorite;

}

int getDecimalValue(string str) {

	string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int decValue = 0;
	int length = str.length();

	for (int i = 0; i < length; i++) {
		int pos = base64.find(str.at(i), 0);
		decValue += pos * (int)pow(64, length - i - 1);
	}

	return decValue;
}

int check(const char* w) {

	string text = w;
	int len = text.length();

	if ((text.find('@', 0) != -1 && text.find('@', 0) != 4294967295) || (text.find('*', 0) != -1 && text.find('*', 0) != 4294967295))
		return 0;
	else
		return 1;

}

string editMeaning(string meaning) {
	
	meaning.replace(0, 1, "");
	int pos = 10;
	while (meaning.find('-', pos + 3) != -1 && meaning.find('-', pos + 3) != 4294967295) {
		pos = meaning.find('-', pos + 3);
		meaning.replace(pos, 1, u8"   ●");
	}

	pos = -2;
	while (meaning.find('=', pos + 2) != -1 && meaning.find('=', pos + 2) != 4294967295) {
		pos = meaning.find('=', pos + 2);
		meaning.replace(pos, 1, u8"- ");
		meaning.insert(pos, "\t");
	}

	pos = -1;
	while (meaning.find('+', pos + 1) != -1 && meaning.find('+', pos + 1) != 4294967295) {
		pos = meaning.find('+', pos + 1);
		meaning.replace(pos, 1, ":");
	}

	pos = -3;
	while (meaning.find('*', pos + 3) != -1 && meaning.find('*', pos + 3) != 4294967295) {
		pos = meaning.find('*', pos + 3);
		meaning.insert(pos, "\n\n");
	}

	return meaning;

}

string editAddMeaning(string meaning) {

	meaning.insert(meaning.find('\n', 0), "\n\n");
	return meaning;

}

string getMeaning(word w) {

	fstream f;
	string meaning = "";

	try {
		f.open("AnhViet.dict", ios::in);
		int begin = w.getBegin10();
		int length = w.getLength10();
		f.seekp(begin, ios::beg);
		char buff[20000];
		f.read(buff, length);
		meaning = buff;
		meaning.replace(length, meaning.length() - length, "");
		f.close();
	}
	catch (exception e) {
	}

	return editMeaning(meaning);

}

void addWordToFile(const char* name, const char* wtype, const char* mean) {

	fstream f;
	try {
		f.open("addword.dict");
		f.seekp(0, ios::end);
		f << "\n@" << name << "\t" << name << "\n";
		f << "* " << wtype << "\n";
		f << u8"   ● " << mean;
		f.close();
	}
	catch (exception e) {

	}
}

void deleteWordFromFile(const char* w) {

	fstream f;
	string line;
	string text = "";

	try {
		f.open("addword.dict", ios::in);
		while (!f.eof()) {
			getline(f, line);
			text += "\n" + line;
		}
		f.close();

		text.replace(0, 1, "");

		int pos = text.find(w, 0) - 1;
		text.replace(pos, text.find('@', pos + 3) - pos, "");

		f.open("addword.dict", ios::out);
		f << text;
		f.close();
	}
	catch (exception e) {

	}
}

void addWordToHistoryFile(const char* w) {

	fstream f;
	try {
		f.open("history.dict", ios::in);
		string text = "";
		string line;

		while (!f.eof()) {
			getline(f, line);
			text += "\n" + line;
		}
		f.close();

		string a = w;
		a = "\n" + a;
		text.replace(0, 1, "");
		text.replace(0, 0, a);
		f.open("history.dict", ios::out);
		f << text;
		f.close();
	}
	catch (exception e) {

	}
}

void deleteWordFromHistoryFile(const char* w) {

	fstream f;
	string text = "";
	string line;

	try {
		f.open("history.dict", ios::in);
		while (!f.eof()) {
			getline(f, line);
			text += "\n" + line;
		}
		f.close();

		text.replace(0, 1, "");

		string a = w;
		a += "\n";

		int pos = text.find(a, 0);
		text.replace(pos - 1, text.find('\n', pos + 1) - pos + 1, "");

		f.open("history.dict", ios::out);
		f << text;
		f.close();

	}
	catch (exception e) {

	}
}

void addWordToFavoriteFile(const char* w) {

	fstream f;
	try {
		f.open("favorite.dict", ios::in);
		string text = "";
		string line;

		while (!f.eof()) {
			getline(f, line);
			text += "\n" + line;
		}
		f.close();

		string a = w;
		a = "\n" + a;
		text.replace(0, 1, "");
		text.replace(0, 0, a);
		f.open("favorite.dict", ios::out);
		f << text;
		f.close();
	}
	catch (exception e) {

	}
}

void deleteWordFromFavoriteFile(const char* w) {

	fstream f;
	string text = "";
	string line;

	try {
		f.open("favorite.dict", ios::in);
		while (!f.eof()) {
			getline(f, line);
			text += "\n" + line;
		}
		f.close();

		text.replace(0, 1, "");

		string a = w;
		a += "\n";

		int pos = text.find(a, 0);
		text.replace(pos - 1, text.find('\n', pos + 1) - pos + 1, "");

		f.open("favorite.dict", ios::out);
		f << text;
		f.close();

	}
	catch (exception e) {

	}
}