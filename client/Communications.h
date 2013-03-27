#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

class SocketClient
{
  private:
  struct sockaddr_in remotesocketinfo;
  struct hostent* hptr;
  int sock;
  //<C-F7>int port;
  //char* remote_host;
  public:
  bool sendnow;
  bool bye;
  SocketClient();
  ~SocketClient();
  SocketClient(const char* host, const char* port);
  void getRawData(std::string input, char* buffer, int* size);
  void getFrameData(int* rows, int* columns, int* type, char** data);
  std::vector<unsigned char> getRawFrameData(std::string input);
  std::string sendmessage(std::string message);
};
