#include <sys/ioctl.h>
#include <unistd.h>
#include <err.h>

int main(int ac, char **av){
  if(ioctl(0, TIOCNOTTY)) err(1, "io(TIOCNOTTY)");
  if(ac < 2) return 0;
  execvp(av[1], av + 1);
  err(1, "execvp %s", av[1]);
}