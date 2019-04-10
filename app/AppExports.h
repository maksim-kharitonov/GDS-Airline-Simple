#pragma once
#ifndef AppExports_h
#define AppExports_h

#ifdef _WIN32
#define clrscr() system("cls");
#endif // _WIN32

#ifdef linux
#define clrscr() system("clear");
#endif // linux

#include "ConfigReader.h"
#include "Command.h"
#include "GdsExports.h"
#include "Tools.h"
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

typedef core::BaseGDS *(__cdecl *GdsFactory)();

void CallDLLByExplicitLinking(string s, LPCSTR dllName);
int executeCommand(Command &command);

#endif // AppExports_h