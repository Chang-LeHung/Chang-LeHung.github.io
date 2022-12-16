pthread resources：

- http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
- https://www.oreilly.com/library/view/pthreads-programming/9781449364724/ch04.html#setting_thread_attributes
- https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/aixprggd/genprogc/term_threads.htm

Thread Basics:

* Thread operations include thread creation, termination, synchronization (joins,blocking), scheduling, data management and process interaction.
* A thread does not maintain a list of created threads, nor does it know the thread that created it.
* All threads within a process share the same address space.
* Threads in the same process share:
  * Process instructions
  * Most data
  * open files (descriptors)
  * signals and signal handlers
  * current working directory
  * User and group id
* Each thread has a unique:
  * Thread ID
  * set of registers, stack pointer
  * stack for local variables, return addresses
  * signal mask
  * priority
  * Return value: errno
* pthread functions return "0" if OK.

why not need to wake up a pthread_join thread ?

https://stackoverflow.com/questions/73807754/how-one-pthread-waits-for-another-to-finish-via-futex-in-linux
