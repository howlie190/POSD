#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
using std :: string;
class Atom;
class Number;
class Variable {
private:
	const string _symbol;
	string _value;
	bool _assignable = true;
public:
	Variable(string s);
	string get_value();
	string get_symbol();
	void set_value(string key);
	bool get_assignable();
	void set_assignable(bool key);
	bool match(Number operand);
	bool match(Atom operand);
};
#endif