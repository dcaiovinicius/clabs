#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUFFER_SIZE (1024 * (EVENT_SIZE + 16))

static void handle_events(const char *stream) {
  int fd = inotify_init();

  if(fd == -1) {
    perror("inotify_init");
    exit(1);
  }

  int wd = inotify_add_watch(fd, stream, IN_MODIFY);

  if(wd == -1) {
    perror("inotify_add_watch");
    close(fd);
    exit(1);
  }

  uint8_t buffer[EVENT_BUFFER_SIZE];
  ssize_t len;
  struct inotify_event *event;

  for(;;) {
    printf("Listening for events\n");

    len = read(fd, buffer, EVENT_BUFFER_SIZE);

    for(uint8_t *ptr = buffer; ptr < buffer + len; ptr += EVENT_SIZE + event->len) {
      event = (struct inotify_event *) ptr;

      if(event->mask & IN_MODIFY) {
        printf("Change\n");
      }
    }
  }

  if(inotify_rm_watch(fd, wd) == -1) {
    perror("inotify_rm_watch");
    exit(1);
  }

  close(fd);
}

int main() {
  handle_events("/tmp/file.txt");
}
