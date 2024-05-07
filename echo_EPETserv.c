#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50

void setnonblockingmode(int fd);
void error_handling(char *buf);

int main(int argc, char *argv[])
{
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t adr_sz;
  int str_len, i;
  char buf[BUF_SIZE];

  struct epoll_event *ep_events;
  struct epoll_event event;
  int epfd, event_cnt;
  if (argc != 2)
  {
    printf("Usage : %s \n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1)
    error_handling("socket() error!");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_address.s_addr = htonl(INADDR_ANY)
}

void error_handling(char *buf)
{
  fputs(buf, stderr);
  fputs("\n", stderr);
  exit(1);
}
