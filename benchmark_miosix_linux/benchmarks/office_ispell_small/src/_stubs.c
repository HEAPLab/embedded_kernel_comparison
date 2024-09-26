#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

#ifndef MIBENCH_LINUX

int access(const char *path, int mode)
{
    return 0;
}

int chmod(const char *path, mode_t mode)
{
    return 0;
}

_sig_func_ptr signal(int sig, _sig_func_ptr func)
{
    return NULL;
}

pid_t fork(void)
{
    return -1;
}

int _execve(const char *path, char *const argv[], char *const envp[])
{
    return -1;
}

#endif

