#pragma once
#ifndef AMADEUSHTTPCLIENT_H
#define AMADEUSHTTPCLIENT_H

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

using namespace std;

class AmadeusHttpClient {
 public:
  AmadeusHttpClient(char *hostname, int port);
  ~AmadeusHttpClient();
  string get(string &request);
  string post(string &request, string &data);
 private:
  SOCKET _socket;
  char *_hostname;
  int _port;
  AmadeusHttpClient();
  static int getHeaderLength(char *content);
  static SOCKET OpenConnection(const char *hostname, int port);
};

#endif  // !AMADEUSHTTPCLIENT_H
