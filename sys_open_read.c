#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if(argc != 2) exit(1);

  // A new file descriptor is opened
  int fd = open(argv[1], O_RDONLY);

  if(fd == -1) {
    fprintf(stderr, "Falied to open file");
    close(fd);
    exit(1);
  }

  unsigned char buffer[20];

  // ssize_t read(int fildes, void *buf, size_t nbyte);
  ssize_t len = read(fd, buffer, sizeof(buffer));

  // ssize_t write(int fildes, const void *buf, size_t nbyte);
  write(1, buffer, len);
}
