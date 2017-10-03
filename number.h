#ifndef NUMBER_H
#define NUMBER_H
#include <string>
using std :: string;
class Atom;
class Variable;
class Number {
private:
	const int _value;
public:
	Number(int);
	bool match(Atom operand);
	bool match(Number operand);
	bool match(Variable &operand);
	string value();
	string symbol();
};
#endif