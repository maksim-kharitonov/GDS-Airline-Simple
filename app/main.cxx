using namespace std;

#include "AppExports.h"

int main(int argc, char *argv[]) {
  clrscr();
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "....... WELCOME TO THE SIMPLE GDS CONSOLE .........." << endl;
  cout << "....... author: Kharitonov M.A.           .........." << endl;
  cout << "....... for MPGU univercity               .........." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  for (string command; cout << "GDS > " && getline(cin, command);) {
    if (!command.empty()) {
      try {
        int res = CommandFactory::CreateCommand(command)->execute();
        switch (res) {
          case 0:
            // normal result
            continue;
          case 1:
            // normal exit
            break;
          case 2:
            // error result
            cout << "Unknown command. Print HELP to get list of available "
                    "commands."
                 << endl;
            continue;
        }
        break;
      } catch (CommandException &e) {
        cerr << e.getCode() << "::" << e.what() << endl;
      }
    }
  }

  Command::destroy();
  std::cout << "Goodbye." << endl;

  return 0;
}