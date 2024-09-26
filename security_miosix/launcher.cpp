
// Kernel-side program to start a userspace process

#include <cstdio>
#include <sys/wait.h>
#include <signal.h>
//#include <spawn.h>
#include "kernel/process.h"

using namespace std;

void run()
{
    pid_t pid;
    int ec;
    //const char *arg[] = { "/bin/exploit", nullptr };
    //const char *env[] = { nullptr };
    //ec=posix_spawn(&pid,arg[0],NULL,NULL,(char* const*)arg,(char* const*)env);
    //if(ec!=0)
    //{
    //    iprintf("spawn returned %d\n",ec);
    //    return;
    //}
    pid=miosix::Process::spawn("/bin/exploit");
    if(pid<0)
    {
        iprintf("spawn returned %d\n",pid);
        return;
    }
    pid=wait(&ec);
    iprintf("pid %d exited\n",pid);
    if(WIFEXITED(ec))
    {
        iprintf("Exit code is %d\n",WEXITSTATUS(ec));
    } else if(WIFSIGNALED(ec)) {
        if(WTERMSIG(ec)==SIGSEGV) iprintf("Process segfaulted\n");
        else iprintf("Process terminated due to an error\n");
    }
}

int main()
{
    for(;;) run();
    return 0;
}
