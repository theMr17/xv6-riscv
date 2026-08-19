#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(2, "syntax: head <file> <line_count>\n");
    exit(1);
  }

  int fd, i = 0;
  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    fprintf(2, "head: cannot open %s\n", argv[1]);
    exit(1);
  }

  char buf[512];
  int n;
  while (i < atoi(argv[2]) && (n = read(fd, buf, sizeof(buf))) > 0) {
    for (int j = 0; j < n; j++) {
      write(1, &buf[j], 1);

      if (buf[j] == '\n') {
        i++;

        if (i == atoi(argv[2]))
          break;
      }
    }
  }

  close(fd);
  exit(0);
}