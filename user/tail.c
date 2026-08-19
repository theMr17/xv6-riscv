#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/stat.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(2, "syntax: tail <file> <line_count>\n");
    exit(1);
  }

  int fd;
  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    fprintf(2, "tail: cannot open %s\n", argv[1]);
    exit(1);
  }

  struct stat st;
  if (fstat(fd, &st) < 0) {
    fprintf(2, "tail: cannot stat %s\n", argv[1]);
    close(fd);
    exit(1);
  }

  char *buf = malloc(st.size);
  int n = read(fd, buf, st.size);

  if (n < 0) {
    fprintf(2, "tail: read error\n");
    close(fd);
    exit(1);
  }

  int newLineCount = 0;
  int writePtr = n;

  for (int j = n - 1; j >= 0; j--) {
    if (buf[j] == '\n') {
      newLineCount++;

      if (newLineCount == atoi(argv[2])) {
        writePtr = j + 1;
        break;
      }
    }
  }

  if (newLineCount < atoi(argv[2])) {
    writePtr = 0;
  }

  write(1, buf + writePtr, n - writePtr);
  write(1, "\n", 1);

  close(fd);
  exit(0);
}
