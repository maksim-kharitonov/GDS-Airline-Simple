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
#include "GdsFactory.h"
#include "Gds.h"
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

#endif // AppExports_h