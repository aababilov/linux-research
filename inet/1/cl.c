#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
  struct sockaddr_in my_addr = {0}, th_addr;
  int connfd, th_sz, i; static char buf[1024] = "Hello";
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(7500);
  inet_aton("127.0.0.1", &my_addr.sin_addr);

  connfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Sock fd %d\t", connfd);
  connect(connfd, (struct sockaddr*) &my_addr, sizeof my_addr);
  printf("Send: %d\n", send(connfd, buf, 4, 0));
  close(connfd);
  
  return 0;
}
