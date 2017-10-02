#ifndef NUMBER_H
#define NUMBER_H
#include <string>
using std :: string;
class Atom;
class Variable;
class Number {
private:
	const string _symbol;
	const int _value;
public:
	Number(string, int);
	Number(int);
	bool match(Atom operand);
	bool match(Number operand);
	bool match(Variable &operand);
	string value();
	string symbol();
};
#endif