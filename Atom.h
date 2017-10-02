#ifndef ATOM_H
#define ATOM_H
#include <string>
using std :: string;
class Number;
class Variable;
class Atom {
private:
	const string _symbol;
public:
	Atom(string);
	bool match(Number operand);
	bool match(Variable &variable);
	bool match(Atom operand);
	string get_symbol();
};
#endif