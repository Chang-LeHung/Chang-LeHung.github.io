#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

static int              /* Start function for cloned child */
childFunc(void *arg)
{
    printf("In child thread and tid = %ld\n", (long int)gettid());
    sleep(5);
    return 0;           /* Child terminates now */
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

int
main(int argc, char *argv[])
{
    char *stack;                    /* Start of stack buffer */
    char *stackTop;                 /* End of stack buffer */
    pid_t pid;
    struct utsname uts;
    /* Allocate memory to be used for the stack of the child */
    stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    if (stack == MAP_FAILED)
        errExit("mmap");

    stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

    /* Create child that has its own UTS namespace;
      child commences execution in childFunc() */
    long int spid = 0;
    long int scid = 0;
    pid = clone(childFunc, stackTop, SIGCHLD | CLONE_CHILD_SETTID | CLONE_PARENT_SETTID, argv[1], &spid, NULL, &scid);
    if (pid == -1)
        errExit("clone");
    printf("clone() returned %ld\n", (long) pid);
    printf("scid = %ld spid = %ld\n", scid, spid);
    if (waitpid(pid, NULL, 0) == -1)    /* Wait for child */
        errExit("waitpid");
    printf("child has terminated\n");

    exit(EXIT_SUCCESS);
}