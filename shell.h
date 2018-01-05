#ifndef SHELL_H
#define SHELL_H

#include "parser.h"


class Shell {
private:
    bool check = false, comma = false, semicolon = false, semicolonTrue = false;
    std :: vector<string>strPool, strPool2;
public:
    string interpret(string input) {
        Scanner scanner(input);
        Parser parser(scanner);
        parser.buildExpression();
        return interpret(parser.getExpressionTree());
    }
    string interpret(Exp *exp) {
        bool ret = exp->evaluate(), sign[3] = {true, true, true};
        string str = exp->getStr(), strforSign1;
        LDR(exp, sign);
        if(ret) {
            if(!sign[1] && !sign[0])
                return "true.";
            if(!sign[1]) {
                for(int i = 0; i < strPool.size(); i++)
                    strforSign1 += strPool[i];
                return strforSign1 + '.';
                
            } else if(!sign[2]) {
                for(int i = 0; i < strPool2.size(); i++)
                    strforSign1 += strPool2[i];
                return strforSign1 + '.';
            } else if(sign[0]) {
                return str + '.';
            } else if(!strPool2.empty()) {
                for(int i = 0; i < strPool2.size(); i++)
                    strforSign1 += strPool2[i];
                return strforSign1 + '.';
            }
            return "true.";
        } else {
            return "false.";
        }
    }
    void LDR(Exp *root, bool sign[]) {
        if(root) {
            LDR(root->getLeftExp(), sign);
            if(root->getOperator() == '=' && !semicolon) {
                if(root->getLeftTerm()->symbol() == root->getRightTerm()->symbol()) {
                    sign[0] = false;
                    check = true;
                    if(comma) {
                        strPool2.pop_back();
                        comma = false;
                    }
                }
                else
                    strPool2.push_back(root->getStr());
                std :: vector<string> :: iterator _find = std :: find(strPool.begin(), strPool.end(), root->getStr());
                if(_find == strPool.end() || semicolonTrue)
                    strPool.push_back(root->getStr());
                else {
                    sign[1] = false;
                    strPool.pop_back();
                }
                
            } else if(root->getOperator() == ',' && !semicolon) {
                strPool.push_back(", ");
                if(check) {
                    check = false;
                }
                else {
                    strPool2.push_back(", ");
                    comma = true;
                }
            } else if(root->getOperator() == ';') {
                sign[2] = false;
                if(root->getLeftExp()->evaluate() && root->getRightExp()->evaluate()) {
                    strPool2.push_back("; ");
                    semicolonTrue = true;
                }
                else
                    semicolon = true;
            }
            LDR(root->getRightExp(), sign);
        }
    }
};

#endif