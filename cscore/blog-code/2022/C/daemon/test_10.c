#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static void  
sig(int signo, siginfo_t* si, void* ucontext)
{
    printf("SIGHUP received, pid = %ld sendid = %d signo = %d\n", 
        (long)getpid(), si->si_pid, signo);
}

int
main(void)
{
    pid_t   pid;

    pid = fork();
    if (pid > 0) {       // parent 
        sleep(1);
        _exit(0);         // parent exit;
    } else {
        struct sigaction s;
        s.sa_flags |= SA_SIGINFO;
        s.sa_handler = sig;
        sigaction(SIGHUP, &s, NULL); 
        sigaction(SIGCONT, &s, NULL); 
        kill(getpid(), SIGSTOP);
    }
    exit(0);
}