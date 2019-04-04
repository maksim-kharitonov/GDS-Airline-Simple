#include "ConfigReader.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
using namespace std;

ConfigReader::ConfigReader(const string &filename) {
  _fileName = filename;
}

ConfigReader::~ConfigReader() {}

map<string, string> ConfigReader::getSection(const string &section) {
  const int bufferSize = 10000;
  char buffer[bufferSize] = "";
  map<string, string> result;

  int charsRead = 0;

  charsRead = GetPrivateProfileSection(section.c_str(), buffer, bufferSize, _fileName.c_str());

  if ((0 < charsRead) && ((bufferSize - 2) > charsRead)) {
    const char *pSubstr = buffer;

    while ('\0' != *pSubstr) {
      size_t substrLen = strlen(pSubstr);
      const char *pos = strchr(pSubstr, '=');
      if (NULL != pos) {
        char name[256] = "";
        char value[256] = "";

        strncpy_s(name, _countof(name), pSubstr, pos - pSubstr);
        strncpy_s(value, _countof(value), pos + 1, substrLen - (pos - pSubstr));
        result[name] = value;
      }

      pSubstr += (substrLen + 1);
    }
  }

  return result;
}
