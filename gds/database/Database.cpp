#include "Database.h"
#include "Detail.h"

inline void Database::shell() {
  char *password;
  char *pass = "codewithc";
  password = getpass("Enter the admininistrator password:");
  Detail a;
  fstream f;
  int ch;
  char c;
  if (strcmp(pass, password) != 0) {
    cout << "Enter the password correctly " << endl;
    cout << "You are not permitted to logon this mode" << endl;
    goto h;
  }
  if (strcmp(pass, password) == 0) {
    char c;
    do {
      cout << "...........ADMINISTRATOR MENU..........." << endl;
      cout << "1. Create detail data base" << endl;
      cout << "2. Add details" << endl;
      cout << "3. Display details" << endl;
      cout << "4. User management" << endl;
      cout << "5. Display passenger details" << endl;
      cout << "6. Return to main menu" << endl;
      cout << "Enter your choice:";
      cin >> ch;

      cout << endl;
      switch (ch) {
      case 1:
        f.open("t.txt", ios::out | ios::binary);
        do {
          a.getdetail();
          f.write((char *)&a, sizeof(a));
          cout << "Do you want to add one more record?" << endl;
          cout << "y-for Yes\nn-for No" << endl;
          cin >> c;
        } while (c == 'y');
        f.close();
        break;
      case 2:
        f.open("t.txt", ios::in | ios::out | ios::binary | ios::app);
        a.getdetail();
        f.write((char *)&a, sizeof(a));
        f.close();
        break;
      case 3:
        f.open("t.txt", ios::in | ios::out | ios::binary | ios::app);
        f.seekg(0);
        while (f.read((char *)&a, sizeof(a))) {
          a.displaydetail();
        }
        f.close();
        break;
      case 4:
        manage();
        break;
      case 5:
        displaypassdetail();
        break;
      }
    } while (ch <= 5);

    f.close();
  }
h:
}