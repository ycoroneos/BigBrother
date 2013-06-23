#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <ctime>

class SocketServer
{
  private:
	struct addrinfo host_nfo, client_nfo;
	struct addrinfo *host_nfo_list;
  struct sockaddr_storage their_addr;
  int host_socket, client_socket;
  public:
  bool sendnow;
  bool next;
  bool bye;
  SocketServer();
  ~SocketServer();
  SocketServer(std::string port);
  int waitmessage();
  void receiveMessage(char* buffer, int buflen);
  void sendmessage(std::string message);
  void Listen();
  void sendraw(char* data, int size);
  bool ping();
  int sendcompressedframe(std::vector<unsigned char> buffer);
};
