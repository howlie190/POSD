#ifndef ATOM_H
#define ATOM_H
#include <string>
using std :: string;
class Number;
class Var;
class Atom {
private:
	const string _symbol;
public:
	Atom(string s);
	string symbol();
	bool match(Number operand);
	bool match(Var &operand);
	bool match(Atom operand);
};
#endif