#include "number.h"
#include "variable.h"
#include "atom.h"
#include <string>
#include <sstream>
using std :: string;
Number :: Number(string s, int i) : _symbol(s), _value(i) {}
Number :: Number(int i) : _value(i) {}
bool Number :: match(Atom operand) { return false; }
bool Number :: match(Number operand) {
	std :: stringstream ss;
	int value;
	ss << operand.value();
	ss >> value;
	return _value == value;
}
bool Number :: match(Var &operand) {
	string value;
	std :: stringstream ss;
	ss << _value;
	ss >> value;
	if(operand.assignable() || operand.value() == value) {
		operand.set_value(value);
		operand.set_assignable(false);
		return true;
	}
	return false;
}
string Number :: value() {
	std :: stringstream ss;
	ss << _value;
	return ss.str();
}
string Number :: symbol() { return _symbol; }