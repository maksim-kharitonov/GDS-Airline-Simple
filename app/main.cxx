using namespace std;

#include "AppExports.h"

map<string, string> gdsModulesStrings;

int main(int argc, char *argv[]) {
  clrscr();
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "....... WELCOME TO THE SIMPLE GDS CONSOLE .........." << endl;
  cout << "....... author: Kharitonov M.A.           .........." << endl;
  cout << "....... for MPGU univercity               .........." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  ConfigReader *config = new ConfigReader("./conf/config.ini");
  gdsModulesStrings = config->getSection("GDS_MODULE_LIST");

  for (string command; cout << "GDS > " && getline(cin, command);) {
    if (!command.empty()) {
      Command cmd;
      try {
        cmd = Command(command);
        int res = executeCommand(cmd);
        switch (res) {
        case 0:
          break;
        case 1:
          delete config;
          std::cout << "Goodbye." << endl;
          exit(0);
        case 2:
          cout << "Unknown command. Print HELP to get list of available "
                  "commands."
               << endl;
          break;
        }
      } catch (CommandException &e) {
        cerr << e.getCode() << "::" << e.what() << endl;
      }
    }
  }

  return 0;
}

int executeCommand(Command &cmd) {
  string command = cmd.getCommandCode();
  if (command == "MODULES") {
    cout << "----------- Available module list: -----------------" << endl;
    for (auto it = gdsModulesStrings.cbegin(); it != gdsModulesStrings.cend();
         ++it) {
      cout << it->first << " " << it->second << endl;
    }
    return 0;
  } else if (command == "SAY") {
    string gds = tools::lowercase_copy(cmd.getModifier());
    if (gds == "") {
      for (auto it = gdsModulesStrings.cbegin(); it != gdsModulesStrings.cend();
           ++it) {
        CallDLLByExplicitLinking(cmd.getParamString(), it->second.c_str());
      }
    } else {
      CallDLLByExplicitLinking(cmd.getParamString(), gdsModulesStrings[gds].c_str());
    }
    
    return 0;
  } else if (command == "EXIT") {
    return 1;
  } else {
    return 2;
  }
}

core::BaseGDS *initGdsByDllName(LPCSTR dllName) {
  HMODULE dll = LoadLibrary(dllName);
  if (!dll) {
    throw "Fail to load library";
  }
  GdsFactory factory =
      reinterpret_cast<GdsFactory>(GetProcAddress(dll, "CreateGDS"));

  if (!factory) {
    FreeLibrary(dll);
    throw "Unable to load CreateGDS from DLL";
  }

  core::BaseGDS *instance = factory();
  return instance;
}

void CallDLLByExplicitLinking(string s, LPCSTR dllName) {
  HMODULE dll = LoadLibrary(dllName);
  if (!dll) {
    cout << "Fail load library" << endl;
    return;
  }

  GdsFactory factory =
      reinterpret_cast<GdsFactory>(GetProcAddress(dll, "CreateGDS"));

  if (!factory) {
    cerr << "Unable to load CreateGDS from DLL!\n";
    FreeLibrary(dll);
    return;
  }

  core::BaseGDS *instance = factory();
  cout << instance->Say(s) << endl;

  instance->Destroy();

  FreeLibrary(dll);

  cout << endl
       << "==============================================================="
       << endl;
}
