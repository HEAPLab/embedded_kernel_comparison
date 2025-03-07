#include <cstdio>
#include <sys/wait.h>
#include <signal.h>
#include "miosix.h"
#include "kernel/process.h"

using namespace std;
using namespace miosix;

int main()
{
    Process::spawn("/bin/benchmark-spawn");
    int ec;
    Process::wait(&ec);
    if (WIFEXITED(ec)) {
        iprintf("Exit code is %d\n", WEXITSTATUS(ec));
    } else if (WIFSIGNALED(ec)) {
        if (WTERMSIG(ec)==SIGSEGV)
            iprintf("Process segfaulted\n");
        // else... what happens?
    }
}
