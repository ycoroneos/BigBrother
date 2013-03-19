#include "Communications.h"
using namespace std;

SocketServer::SocketServer(string port)
{
    sendnow=false;
    memset(&host_nfo, 0, sizeof(host_nfo));
    memset(&client_nfo, 0, sizeof(client_nfo));
    std::cout << "setting up structs\n";
    host_nfo.ai_family=AF_UNSPEC;
    host_nfo.ai_socktype=SOCK_STREAM;
    host_nfo.ai_flags=AI_PASSIVE;
    int status=getaddrinfo(NULL, port.c_str(), &host_nfo, &host_nfo_list);
    if (status==-1) cout << "failed getting host info\n";
    host_socket=socket(host_nfo_list->ai_family, host_nfo_list->ai_socktype, host_nfo_list->ai_protocol);
    if (host_socket==-1) cout << "socket error\n";
    int yes=1;
    setsockopt(host_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(host_socket, host_nfo_list->ai_addr, host_nfo_list->ai_addrlen)==-1) cout << "couldn't bind socket\n";
    if (listen(host_socket, 10)==-1) cout << "listen error\n";
    else cout << "listening now\n";
    socklen_t addr_size = sizeof(their_addr);
    client_socket = accept(host_socket, (struct sockaddr *)&their_addr, &addr_size);
    if (client_socket==-1)
        cout << "listen error\n";
    else
        cout << "accepted a client " << client_socket << " \n";
}

SocketServer::SocketServer()
{
}

SocketServer::~SocketServer()
{
    freeaddrinfo(host_nfo_list);
    close(client_socket);
    close(host_socket);
}

int SocketServer::waitmessage()
{
    while(1)
    {
        ssize_t bytes_recieved;
        char incomming_data_buffer[20];
        bytes_recieved = recv(client_socket, incomming_data_buffer,10, 0);
        incomming_data_buffer[bytes_recieved] = '\0';
        int val=strncmp(incomming_data_buffer, "image", 5);
        if (val==0)
        {
            sendnow=true;
        }
        else if (strncmp(incomming_data_buffer, "next", 4)==0)
        {
          next=true;
        }
        else if (strncmp(incomming_data_buffer, "bye", 3)==0)
        {
            bye=true;
            break;
        }
    }
    return 0;
}

void SocketServer::sendmessage(string message)
{
    send(client_socket, message.c_str(), message.size(), 0);
}

void SocketServer::sendframe(int rows, int columns, int type, char* data)
{
  char buf[10];
  sprintf(buf, "%d", rows);
  send(client_socket, buf, strlen(buf), 0);
  memset(buf, '0', sizeof(buf));
  sprintf(buf, "%d", columns);

  while (next==false) {}
  send(client_socket, buf, strlen(buf), 0);
  next=false;
  memset(buf, '0', 10);
  sprintf(buf, "%d", type);

  while (next==false) {}
  send(client_socket, buf, strlen(buf), 0);
  next=false;
  memset(buf, '0', 10);
  sprintf(buf, "%d", strlen(data));

  while (next==false) {}
  send(client_socket, buf, strlen(buf), 0);

  while (next==false) {}
  send(client_socket, data, strlen(data), 0);
}

void SocketServer::sendcompressedframe(std::vector<char> buffer)
{
  char buflen[250];
  sprintf(buflen, "%d", buffer.size());
  send(client_socket, buflen, 250, 0);
  send(client_socket, &buffer, buffer.size(), 0);
}

void SocketServer::sendraw(char* data, int size)
{
  send(client_socket, data, size, 0);
}
