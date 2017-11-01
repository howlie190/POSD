#ifndef profile_h
#define profile_h

#include <string>
#include <algorithm>
#include <vector>

using std :: string;
using std :: vector;
using std :: pair;

class Symtable {
protected:
    const int NONE = -1;
    const int EOS = '\0';
    const int NUMBER = 256;
    const int ATOM = 257;
    const int ATOMSC = 258;
    const int VAR = 259;
    vector<pair<string, int>>_symTable;
public:
    bool isSpecialCh(char c) {
        return c == '+'
            // || c == '=' // ... the matching operator
               || c == '-'
               || c == '*'
               || c == '/'
               || c == '<'
               || c == '>'
               || c == '.'
               || c == '&'
               || c == '\\'
               || c == '~'
               || c == '^'
               || c == '$'
               || c == '#'
               || c == '@'
               || c == '?'
               || c == ':';
    
    }
    bool symbolExist(string s, int &val) {
        bool found = false;
        val = -1;
        vector<pair<string, int>>:: iterator it = find_if(_symTable.begin(), _symTable.end(), [s](pair<string, int>ele) {
            return ele.first == s;
        });
        found = _symTable.end() != it;
        if(found) {
            val = it - _symTable.begin();
            return found;
        }
    }
};

#endif