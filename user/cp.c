#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/stat.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(2, "syntax: cp source destination\n");
    exit(1);
  }

  char *src = argv[1];
  char *dest = argv[2];

  int srcFd = open(src, O_RDONLY);
  int destFd = open(dest, O_WRONLY | O_CREATE | O_TRUNC);

  if (srcFd < 0) {
    fprintf(2, "cp: cannot open %s\n", src);
    exit(1);
  }

  if (destFd < 0) {
    fprintf(2, "cp: cannot open %s\n", dest);
    exit(1);
  }

  struct stat st;
  if (fstat(srcFd, &st)) {
    fprintf(2, "cp: cannot stat %s\n", src);
    exit(1);
  }

  char *buf = malloc(st.size);
  int n = read(srcFd, buf, st.size);

  if (write(destFd, buf, n) < 0) {
    fprintf(2, "cp: cannot write %s\n", dest);
    exit(1);
  }

  free(buf);
  close(srcFd);
  close(destFd);
  exit(0);
}