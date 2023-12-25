#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

int main() {
  // Open file in binary mode
  FILE *stream = fopen("/tmp/file.txt", "rb");

  // if
  if(stream == NULL) {
    perror("fopen");
    fclose(stream);
    exit(1);
  }

  uint8_t buffer[BUFFER_SIZE];

  while(!feof(stream)) {
    size_t len = fread(buffer, sizeof(*buffer),
        sizeof(buffer) / sizeof(*buffer), stream);

    fwrite(buffer, sizeof(*buffer), len, stdout);
    printf("Read %zu bytes from the file.txt\n", len);
  }

  fclose(stream); // Close the file stream
}
