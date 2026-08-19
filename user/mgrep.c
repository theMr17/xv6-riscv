#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(2, "syntax: mgrep pattern [files...]\n");
    exit(1);
  }

  int childCount = argc - 2;

  for (int i = 0; i < childCount; i++) {
    int childPid = fork();
    if (childPid == 0) {
      char *args[] = {"grep", argv[1], argv[i + 2], 0};
      exec("grep", args);
      fprintf(2, "cmd: exec %s failed\n", argv[1]);
      exit(1);
    }
  }

  for (int i = 0; i < childCount; i++) {
    wait(0);
  }

  exit(0);
}
