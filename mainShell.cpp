#include "parser.h"
#include "shell.h"
using namespace std;
int main(int argc, char **argv)
{
  Shell shell;
  while(1)
  {
    bool exe = false;
    std::string input;
    std::string executedString;
    input.clear();
    cout << "?- ";
    while(!exe)
    {
      getline(cin,input);
      if(input.empty())
      {
        cout << "?- ";
        continue;
      }
      for(char c : input)
      {
        if(!isspace(c))
          executedString.push_back(c);
        if(c == '.')
        {
          exe = true;
          break;
        }
      }
      if(!exe)
        cout << "|   ";
    }
    if(input == "halt.")
      break;
    try
    {
      std::cout << shell.interpret(executedString) << std::endl;
    }
    catch(std::string s)
    {
      std::cout << s << std::endl;
    }
  }

  return 0;
}