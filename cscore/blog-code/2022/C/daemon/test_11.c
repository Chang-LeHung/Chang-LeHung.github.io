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
sig_hup(int signo) //**never get called ???**
{
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void
pr_ids(char *name)
{
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
        name, (long)getpid(), (long)getppid(), (long)getpgrp(),
        (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int
main(void)
{
    pid_t   pid;

    pr_ids("parent");
    pid = fork();
    if (pid > 0) {       // parent 
        sleep(5);
        _exit(0);         // parent exit;
    } else {
        pr_ids("child");

        /*setsid();        //create new session, and "child" becomes the session leader*/

        pid = fork();
        if(pid>0) {
            sleep(20);
            exit(0);     // "child" exit
                         // so the process group become an orphan process group
        }
        else{
            pr_ids("grandson");
            signal(SIGHUP, sig_hup);    // establish signal handler 
            kill(getpid(), SIGSTOP);
            printf("end\n");
        }
    }
    exit(0);
}