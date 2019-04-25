#ifndef GDSFACTORY_H
#define GDSFACTORY_H
typedef core::BaseGDS *(__cdecl *GdsFactory)(map<string,string> param);
#endif  // !GDSFACTORY_H