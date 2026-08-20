#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int n = 3;
  int pids[3];
  int pid = getpid();

  printf("[parent] pid: %d\n", pid);
  printf("[parent] forking %d children\n", n);

  int ret = nfork(n, pids);
  if (ret == 0) {
    printf("[child] pid: %d, ppid: %d\n", getpid(), getppid());
    exit(0);
  } else if (ret == n) {
    printf("[parent] get_child_count returned %d\n", get_child_count());
    for (int i = 0; i < n; i++) {
      wait(0);
    }
  }

  exit(0);
}
