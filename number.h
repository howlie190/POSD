#ifndef NUMBER_H
#define NUMBER_H
#include <string>
using std :: string;
class Atom;
class Var;
class Number {
private:
	const string _symbol;
	const int _value;
public:
	Number(string, int);
	Number(int);
	bool match(Atom operand);
	bool match(Number operand);
	bool match(Var &operand);
	string value();
	string symbol();
};
#endif