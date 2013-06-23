#include "Communications.h"
using namespace std;

SocketClient::SocketClient(const char* host, const char* port)
{
    //port=atoi(port);
    sendnow=false;
    bye=false;
    sock=socket(AF_INET, SOCK_STREAM, 0);
    bzero(&remotesocketinfo, sizeof(sockaddr_in));
    hptr=gethostbyname(host);
    if (hptr==NULL)
    {
        cout << "couldn't connect to host " << host << endl;
        return;
    }
    remotesocketinfo.sin_family = AF_INET;
    memcpy((char *)&remotesocketinfo.sin_addr, hptr->h_addr, hptr->h_length);
    remotesocketinfo.sin_port = htons((u_short)atoi(port));      // Set port number
    //connect(socket, (struct sockaddr *)&remotesocketinfo, sizeof(sockaddr_in));
    if (connect(sock, (struct sockaddr *)&remotesocketinfo, sizeof(sockaddr_in))<0)
    {
        close(sock);
        cout << "couldn't connect\n";
        return;
    }
    cout << "connected to host and ready to go\n";
}

SocketClient::SocketClient()
{
}

SocketClient::~SocketClient()
{
    close(sock);
}

string SocketClient::sendmessage(string message)
{
    send(sock, message.c_str(), message.length(), 0);
    char response[25];
    recv(sock, response, 25, 0);
    return string(response);
}

void SocketClient::getRawData(std::string input, char* buffer, int* size)
{
    char sizeb[20];
    send(sock, input.c_str(), strlen(input.c_str()), 0);
    recv(sock, sizeb, sizeof(sizeb), 0);
    (*size)=atoi(sizeb);
    buffer=new char[*size];
    recv(sock, buffer, *size, 0);
    return;
}

vector<unsigned int> SocketClient::getRawFrameData(std::string input)
{
    unsigned int size;
    send(sock, input.c_str(), strlen(input.c_str()), 0);
    recv(sock, &size, sizeof(unsigned int), 0);
    vector<unsigned int> buf(size);

    int bytes_received=0;
    while (1)
    {
      int result=recv(sock, &buf[bytes_received/sizeof(unsigned int)], (size*sizeof(unsigned int))-bytes_received, 0);
      bytes_received+=result;
      if (bytes_received>=size*sizeof(unsigned int))
      {
        break;
      }
    }
    return buf;
}

bool SocketClient::waitForPing()
{
  char ping;
  int result=recv(sock, &ping, 1, 0);
  if (result==-1)
  {
    return false;
  }
  else if (ping=='p')
  {
    result=send(sock, (void*)'h', 1, 0);
    if (result==-1)
    {
      return false;
    }
  }
  return true;
}
