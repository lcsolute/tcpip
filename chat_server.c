#include <arpa/inet.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUF_SIZE 100
#define MAX_CLNT 256

void *handle_clnt(void *arg);
void send_msg(char *msg, int len);
void error_handling(char *msg);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc, char *argv[]) {
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_sz;
  pthread_t t_id;
  if (argc != 2) {
    printf("Usage : %s <port> \n", argv[0]);
    exit(1);
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));
  if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    error_handling("bind() error");
  if (listen(serv_sock, MAX_CLNT))
    error_handling("listen() error");

  while (1) {
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
    if (clnt_sock == -1)
      continue;
    pthread_mutex_lock(&mutx);
    clnt_socks[clnt_cnt++] = clnt_sock;
    pthread_mutex_unlock(&mutx);
    // clnt_sock 是基本数据类型，因此会创建副本clnt_sock
    pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_sock);
    pthread_detach(t_id);
    printf("Connected client IP: %s\n", inet_ntoa(clnt_adr.sin_addr));
  }
  close(serv_sock);
  return 0;
}
