#pragma once
using namespace std;

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <map>
#include <string>
#include <Windows.h>

class ConfigReader {
public:
  ConfigReader(const string &filename);
  ~ConfigReader();
  map<string, string> getSection(const string &section);

private:
  string _fileName;
};

#endif // CONFIG_READER_H