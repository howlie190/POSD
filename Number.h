#ifndef NUMBER_H
#define NUMBER_H
#include <string>
using std :: string;
class Atom;
class Variable;
class Number {
private:
	const string _symbol;
	const string _value;
public:
	Number(string, string);
	bool match(Atom operand);
	bool match(Number operand);
	bool match(Variable &variable);
	string value();
	string symbol();
};
#endif