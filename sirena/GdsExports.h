#pragma once

#ifdef _WIN32
#ifdef sirena_EXPORTS
#define Sirena_API __declspec(dllexport)
#else
#define Sirena_API __declspec(dllimport)
#endif // SIRENAWIN32DLL_EXPORTS
#else
#define Sirena_API
#endif

#include <string>

using namespace std;

namespace core {
class BaseGDS {
public:
  virtual void Destroy() { delete this; }

  virtual string Say(string &s) = 0;
  virtual string Search(string &searchString) = 0;
  virtual string Hold(string &offerId) = 0;
  virtual string Book(string &offerId) = 0;
  virtual string Ticket(string &pnr) = 0;
};
} // namespace core