#include "AmadeusHttpClient.h"

AmadeusHttpClient::AmadeusHttpClient() {
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    cout << "WSAStartup failed.\n";
    system("pause");
  }
}

AmadeusHttpClient::AmadeusHttpClient(char* hostname, int port)
    : AmadeusHttpClient() {
  _hostname = hostname;
  _port = port;
}

AmadeusHttpClient::~AmadeusHttpClient() { WSACleanup(); }

int AmadeusHttpClient::getHeaderLength(char* content) {
  const char *srchStr1 = "\r\n\r\n", *srchStr2 = "\n\r\n\r";
  char* findPos;
  int ofset = -1;

  findPos = strstr(content, srchStr1);
  if (findPos != NULL) {
    ofset = findPos - content;
    ofset += strlen(srchStr1);
  } else {
    findPos = strstr(content, srchStr2);
    if (findPos != NULL) {
      ofset = findPos - content;
      ofset += strlen(srchStr2);
    }
  }
  return ofset;
}

string AmadeusHttpClient::get(string& request) {
  const int bufSize = 512;
  char readBuffer[bufSize], sendBuffer[bufSize], tmpBuffer[bufSize];
  char *tmpResult = NULL, *result;
  string server, filepath, filename;
  long totalBytesRead, thisReadSize, headerLen;

  ///////////// step 1, connect //////////////////////
  _socket = OpenConnection(_hostname, _port);

  ///////////// step 2, send GET request /////////////
  sprintf(tmpBuffer, "GET %s HTTP/1.0", request.c_str());
  strcpy(sendBuffer, tmpBuffer);
  strcat(sendBuffer, "\r\n");
  sprintf(tmpBuffer, "Host: %s:%d", _hostname, _port);
  strcat(sendBuffer, tmpBuffer);
  strcat(sendBuffer, "\r\n");
  strcat(sendBuffer, "\r\n");
  send(_socket, sendBuffer, strlen(sendBuffer), 0);

  ///////////// step 3 - get received bytes ////////////////
  // Receive until the peer closes the connection
  totalBytesRead = 0;
  while (1) {
    memset(readBuffer, 0, bufSize);
    thisReadSize = recv(_socket, readBuffer, bufSize, 0);

    if (thisReadSize <= 0) break;

    tmpResult = (char*)realloc(tmpResult, thisReadSize + totalBytesRead);

    memcpy(tmpResult + totalBytesRead, readBuffer, thisReadSize);
    totalBytesRead += thisReadSize;
  }

  headerLen = getHeaderLength(tmpResult);
  long contenLen = totalBytesRead - headerLen;
  result = new char[contenLen + 1];
  memcpy(result, tmpResult + headerLen, contenLen);
  result[contenLen] = 0x0;

  closesocket(_socket);

  return result;
}

string AmadeusHttpClient::post(string& request, string& data) {
  return string();
}

SOCKET AmadeusHttpClient::OpenConnection(const char* hostname, int port) {
  int socketDescriptor, err;
  struct addrinfo hints = {}, *addrs;
  char port_str[16] = {};

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  sprintf(port_str, "%d", port);

  err = getaddrinfo(hostname, port_str, &hints, &addrs);
  if (err != 0) {
    fprintf(stderr, "%s: %s\n", hostname, gai_strerror(err));
    abort();
  }

  for (struct addrinfo* addr = addrs; addr != NULL; addr = addr->ai_next) {
    socketDescriptor =
        socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (socketDescriptor == -1) {
      err = errno;
      break;
    }

    if (connect(socketDescriptor, addr->ai_addr, addr->ai_addrlen) == 0) break;

    err = errno;

    closesocket(socketDescriptor);
    socketDescriptor = -1;
  }

  freeaddrinfo(addrs);

  if (socketDescriptor == -1) {
    fprintf(stderr, "%s: %s\n", hostname, strerror(err));
    abort();
  }

  return socketDescriptor;
}
