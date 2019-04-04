using namespace std;

#include "AppExports.h"

int main(int argc, char *argv[]) {
  clrscr();
  int ch;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "....... WELCOME TO THE SIMPLE GDS CONSOLE .........." << endl;
  cout << "....... author: Kharitonov M.A.           .........." << endl;
  cout << "....... for MPGU univercity               .........." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  ConfigReader *config = new ConfigReader("./conf/config.ini");
  cout << "----------- Available module list: -----------------" << endl;
  map<string, string> gdsModules = config->getSection("GDS_MODULE_LIST");
  for (auto it = gdsModules.cbegin(); it != gdsModules.cend(); ++it) {
    cout << it->first << " " << it->second << endl;
  }

  do {
    cout << "^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^" << endl;
    cout << "1.Admin mode\n2.User mode\n3.Exit\n";
    cout << "Enter your choice: ";
    cin >> ch;
    cout << endl;
    switch (ch) {
    case 1:
      CallDLLByExplicitLinking("Hello", "sirena.dll");
      break;
    case 2:
      CallDLLByExplicitLinking("Hello", "amadeus.dll");
      break;
    case 3:
      exit(0);
    }
  } while (ch <= 3);

  cin.get();

  delete config;
  return 0;
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
