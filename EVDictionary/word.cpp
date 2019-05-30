#include <string>
#include <iostream>
#include "word.h"
#include "Processing.h"

using namespace std;

// class word

int word::isNull() {
	if (this->getBegin() != "")
		return 0;
	else return 1;
}

void word::setName(string name1) {
	this->name = name1;
}

string word::getName() {
	return this->name;
}

void word::setBegin(string begin1) {
	this->begin = begin1;
}

string word::getBegin() {
	return this->begin;
}

void word::setLength(string length1) {
	this->length = length1;
}

string word::getLength() {
	return this->length;
}

void word::setNum(int num1) {
	this->num = num1;
}

int word::getNum() {
	return this->num;
}

int word::getBegin10() {
	return getDecimalValue(this->begin);
}

int word::getLength10() {
	return getDecimalValue(this->length);
}

// class addWord

int addWord::isNull() {
	if (this->getNum() != 0)
		return 0;
	else return 1;
}

void addWord::setName(string name1) {
	this->name = name1;
}

string addWord::getName() {
	return this->name;
}

void addWord::setMeaning(string mean) {
	this->meaning = mean;
	string a = mean.substr(mean.find('\n', 0) + 3, mean.find(u8"   ● ") - mean.find('\n', 0) - 4);
	this->type = a;
	string b = mean.substr(mean.find(u8"   ● ", 0) + 7, mean.length() - mean.find(u8"   ● ", 0) - 7);
	this->inp_mean = b;
}

string addWord::getMeaning() {
	return this->meaning;
}

string addWord::getInp_mean() {
	return this->inp_mean;
}

string addWord::getType() {
	return this->type;
}

void addWord::setNum(int num1) {
	this->num = num1;
}

int addWord::getNum() {
	return this->num;
}