#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include <string>

class word {

	private:
		std::string name;
		std::string begin;
		std::string length;
		int num;

	public:
		int isNull();
		void setName(std::string name1);
		std::string getName();
		void setBegin(std::string begin1);
		std::string getBegin();
		void setLength(std::string length1);
		std::string getLength();
		void setNum(int num1);
		int getNum();
		int getBegin10();
		int getLength10();
};

class addWord {

	private:
		std::string name;
		std::string inp_mean;
		std::string meaning;
		std::string type;
		int num;

	public:
		int isNull();
		void setName(std::string name1);
		std::string getName();
		void setMeaning(std::string mean);
		std::string getMeaning();
		void setInp_mean(std::string mean);
		std::string getInp_mean();
		void setType(std::string type1);
		std::string getType();
		void setNum(int num1);
		int getNum();
};

#endif // WORD_H_INCLUDED