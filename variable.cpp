#include "variable.h"
#include "atom.h"
#include "number.h"
#include <string>
#include <sstream>
using std :: string;
Var :: Var(string s) : _symbol(s) {}
string Var :: value() { return _value; }
string Var :: symbol() { return _symbol; }
void Var :: set_value(string key) { _value = key; }
bool Var :: assignable() { return _assignable; }
void Var :: set_assignable(bool key) { _assignable = key; }
bool Var :: match(Number operand) {
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
bool Var :: match(Atom operand) {
	if(_assignable || _value == operand.symbol()) {
		_value = operand.symbol();
		_assignable = false;
		return true;
	}
	return false;
}