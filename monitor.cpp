#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#define TCPSERVERPORT 25112
#define IPADDR "127.0.0.1"
#define DOMAIN PF_INET // TODO change domain to AF_INET for Unix
#define CLIENT "monitor"

using namespace std;

int createStreamClientSocket()
{
  // Create a socket
  int stream_client_socket; // socket id of client socket

  // Domain = AF_INET  Type = SOCK_STREAM Protocol = 0
  // We let the transport layer decide the protocol based on 'Type'
  if ((stream_client_socket = socket(DOMAIN, SOCK_STREAM, 0)) == -1)
  {
    cerr << "Stream " << CLIENT << " socket could not be created for " << CLIENT;
    return -1;
  }

  string ipAddress = IPADDR; // using loopback address as local IP for client

  // Create a addr hint for the Main/Stream Server
  sockaddr_in stream_server_hint;
  stream_server_hint.sin_family = DOMAIN;
  stream_server_hint.sin_port = htons(TCPSERVERPORT);                 // host to network short
  inet_pton(DOMAIN, ipAddress.c_str(), &stream_server_hint.sin_addr); // inet_pton to convert a number in our IP to array of integers

  // Connect to server
  if (connect(stream_client_socket, (sockaddr *)&stream_server_hint, sizeof(stream_server_hint)) == -1)
  {
    cerr << "Stream " << CLIENT << " socket could not connect to stream serverM";
    return -1;
  }
  return stream_client_socket;
}

int sendRecieve(string messageSend, string messageDisplay, int stream_client_socket)
{
  // Send and Recieve
  char buf[4096];

  // Send to the server
  if (send(stream_client_socket, messageSend.c_str(), messageSend.size() + 1, 0) == -1)
  {
    cerr << "Stream " << CLIENT << " socket could not send to stream serverM. Please try again." << endl;
    close(stream_client_socket);
    return -1;
  }

  cout << messageDisplay << endl;

  // Wait for response and recieve it
  memset(buf, 0, 4096);
  int bytesRecieved = recv(stream_client_socket, buf, 4096, 0);

  if (bytesRecieved == -1)
  {
    cerr << "Stream " << CLIENT << " socket could not recieve stream from serverM. Please try again." << endl;
    close(stream_client_socket);
    return -1;
  }

  // Display response

  cout << string(buf, bytesRecieved) << endl;
  close(stream_client_socket);
  return 0;
}

int listTransaction()
{
  int stream_client_socket = createStreamClientSocket();
  if (stream_client_socket == -1)
  {
    return stream_client_socket;
  }

  // Construct display message
  string messageDisplay = "Monitor sent a sorted list request to the main server.";

  // Send request
  return sendRecieve("TXLIST", messageDisplay, stream_client_socket);
}

int main(int argc, char *argv[])
{
  // Display Boot Message
  cout << "The monitor is up and running." << endl;

  if (argc == 2 && ((string)argv[1]).compare("TXLIST") == 0)
  {
    return listTransaction();
  }
  else
  {
    cerr << CLIENT << " can only accept one parameter : TXLIST" << endl;
    return -1;
  }
}