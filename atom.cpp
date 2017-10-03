#include "atom.h"
#include "number.h"
#include "variable.h"
Atom :: Atom(string s) : _symbol(s) {}
string Atom :: symbol() { return _symbol; }
bool Atom :: match(Number operand) { return false; }
bool Atom :: match(Variable &operand) {
	if(operand.assignable() || _symbol == operand.value()) {
		operand.set_value(_symbol);
		operand.set_assignable(false);
		return true;
	}
	return false;
}
bool Atom :: match(Atom operand) {}