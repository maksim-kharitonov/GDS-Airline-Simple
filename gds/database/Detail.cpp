#include "Detail.h"

inline void Detail::getdetail() {
  cout << "Enter the details as follows" << endl;
  cout << "Train no:";
  cin >> tno;
  cout << "Train name:";
  gets(tname);
  cout << "Boarding point:";
  gets(bp);
  cout << "Destination pt:";
  gets(dest);
  cout << "No of seats in first class & fare per ticket:";
  cin >> c1 >> c1fare;
  cout << "No of seats in second class & fare per ticket:";
  cin >> c2 >> c2fare;
  cout << "Date of travel:";
  cin >> d >> m >> y;
}

void Detail::displaydetail() {
  cout << tno << "\t" << tname << "\t" << bp << "\t" << dest << "\t";
  cout << c1 << "\t" << c1fare << "\t" << c2 << "\t" << c2fare << "\t";
  cout << d << "-" << m << "-" << y << "\t" << endl;
}

Detail::Detail() {}

Detail::~Detail() {}