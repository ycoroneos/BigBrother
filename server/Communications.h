#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

class SocketServer
{
  private:
	struct addrinfo host_nfo, client_nfo;
	struct addrinfo *host_nfo_list;
  struct sockaddr_storage their_addr;
  int host_socket, client_socket;
  public:
  bool sendnow=false;
  bool next=false;
  bool bye=false;
  SocketServer();
  ~SocketServer();
  SocketServer(std::string port);
  int waitmessage();
  void sendmessage(std::string message);
  void sendraw(char* data, int size);
  void sendframe(int rows, int columns, int type, char* data);
  void sendcompressedframe(std::vector<char> buffer);
};
