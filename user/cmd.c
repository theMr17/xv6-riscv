#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc == 1) {
    fprintf(2, "syntax: cmd [commands...]\n");
    exit(1);
  }

  int childPid = fork();

  if (childPid < 0) {
    fprintf(2, "cmd: fork failed\n");
    exit(1);
  }

  if (childPid == 0) {
    exec(argv[1], argv + 1);
    fprintf(2, "cmd: exec %s failed\n", argv[1]);
    exit(1);
  } else {
    wait(&childPid);
  }

  exit(0);
}
