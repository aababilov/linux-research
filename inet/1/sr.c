#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
  struct sockaddr_in my_addr = {0}, th_addr = {0};
  int svfd, connfd, th_sz =2* sizeof th_addr, i;
  static char buf[1024];
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(7500);
  inet_aton("127.0.0.1", &my_addr.sin_addr);
  //my_addr.sin_addr.s_addr = INADDR_ANY;

  svfd = socket(AF_INET, SOCK_STREAM, 0);
  i = fcntl(svfd, F_GETFD, 0);
  fcntl(svfd, F_SETFD, i | O_NONBLOCK);
  bind(svfd, (struct sockaddr *)&my_addr, sizeof my_addr);
  listen(svfd, 512);
  
  fcntl(svfd, F_SETFD, i | O_NONBLOCK);
  connfd = accept(svfd, (struct sockaddr *)&th_addr, &th_sz);
  printf("Conn with %s; fd  %d\n", inet_ntoa(th_addr.sin_addr), connfd);
  i = recv(connfd, buf, 4, 0);
  buf[5] = 0;
  printf("Rec: %s; %d bytes\n", buf, i);
  close(connfd);

  close(svfd);
  return 0;
}
