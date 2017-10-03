#include "variable.h"
#include "atom.h"
#include "number.h"
#include <string>
#include <sstream>
using std :: string;
Variable :: Variable(string s) : _symbol(s) {}
string Variable :: value() { return _value; }
string Variable :: symbol() { return _symbol; }
void Variable :: set_value(string key) { _value = key; }
bool Variable :: assignable() { return _assignable; }
void Variable :: set_assignable(bool key) { _assignable = key; }
bool Variable :: match(Number operand) {
	string value;
	std :: stringstream ss;
	ss << operand.value();
	ss >> value;
	if(_assignable || _value == value) {
		_value = value;
		_assignable = false;
		return true;
	}
	return false;
}
bool Variable :: match(Atom operand) {
	if(_assignable || _value == operand.symbol()) {
		_value = operand.symbol();
		_assignable = false;
		return true;
	}
	return false;
}