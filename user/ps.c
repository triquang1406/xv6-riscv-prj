#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/getprocs.h"

static char *states[] = {
  [0] "unused", 
  [1] "used", 
  [2] "sleep", 
  [3] "runble",
  [4] "run", 
  [5] "zombie"
};

int
main(int argc, char *argv[])
{
  struct procinfo procs[64];
  int nprocs = getprocs(procs, 64);
  
  printf("PID STATE SIZE NAME\n");
  for(int i = 0; i < nprocs; i++) {
    printf("%d %s %d %s\n", 
           procs[i].pid, 
           states[procs[i].state], 
           (int)procs[i].sz,
           procs[i].name);
  }
  exit(0);
}
