#include "Number.h"
#include "Variable.h"
#include "Atom.h"
Number :: Number(string s, string v) : _symbol(s), _value(v) {}
bool Number :: match(Atom operand) { return false; }
bool Number :: match(Number operand) { return _value == operand._value; }
bool Number :: match(Variable &variable) {
	bool ret = variable.get_assignable();
	if(variable.get_assignable() || variable.get_value() == _value) {
		variable.set_value(_value);
		variable.set_assignable(false);
		return true;
	}
	return ret;
}
string Number :: value() { return _value; }
string Number :: symbol() { return _symbol; }