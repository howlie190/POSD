#include "Atom.h"
#include "Number.h"
#include "Variable.h"
using std :: string;
Atom :: Atom(string s) : _symbol(s) {}
bool Atom :: match(Number operand) { return false; }
string Atom :: get_symbol() { return _symbol; }
bool Atom :: match(Variable &variable) {
	bool ret = variable.get_assignable();
	if(variable.get_assignable() || _symbol == variable.get_value()) {
		variable.set_value(_symbol);
		variable.set_assignable(false);
		return true;
	}
	return ret;
}