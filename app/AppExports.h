#pragma once
#ifndef AppExports_h
#define AppExports_h

#ifdef _WIN32
#define clrscr() system("cls");
#endif // _WIN32

#ifdef linux
#define clrscr() system("clear");
#endif // linux

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
#include<iomanip>
#include<fstream>

#endif // AppExports_h