using namespace std;

#include "AppExports.h"

#include "simple/SimpleFunctions.h"
#include "advanced/AdvancedFunctions.h"

int main(int argc, char *argv[])
{
	clrscr();
	int ch;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "....... WELCOME TO THE SIMPLE GDS CONSOLE .........." << endl;
	cout << "....... author: Kharitonov M.A.           .........." << endl;
	cout << "....... for MPGU univercity               .........." << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	do {
		cout << "^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^" << endl;
		cout << "1.Admin mode\n2.User mode\n3.Exit\n";
		cout << "Enter your choice: ";
		cin >> ch;
		cout << endl;
		switch (ch) {
			case 1:
				cout << "case 1" << endl;
				break;
			case 2:
				cout << "case 2" << endl;
				break;
			case 3:
				exit(0);
		}
	} while (ch <= 3);
	getch();
	return 0;
}
