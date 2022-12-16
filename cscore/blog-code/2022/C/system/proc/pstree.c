


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define KiB *(1 << 10)

static
void empty(char* path, int size) {
  for(int i = 0; i <= size; i++) 
  {
    path[i] = ' ';
  }
  path[++size] = '\0';
}

static
void get_process_name_by_pid(int pid, char* name) {
  char cpath[128];
  sprintf(cpath, "/proc/%d/stat", pid);
  FILE* cfp = fopen(cpath, "r");
  fscanf(cfp, "%d %s", &pid, name);
}

static
void dump_process(int pid, int depth, int maxdepth) {

  // find child process id filename
  char path[1 KiB];
  sprintf(path, "/proc/%d/task/%d/children", pid, pid);

  // read child process id from filename abvove
  FILE* fp = fopen(path, "r");
  int cpid;
  get_process_name_by_pid(pid, path);
  printf("%d[label=\"%s(%d)\"];\n", pid, path, pid);
  while(fscanf(fp, "%d", &cpid) != -1) {
    printf("%d->%d;\n", pid, cpid);
    if(maxdepth >= depth) {
      dump_process(cpid, depth, maxdepth);
    }
  }
}

int main(int argc, char *argv[]) {
  printf("digraph processTree{\n");
  dump_process(1, 0, 3);
  printf("}\n");
  return 0;
}
