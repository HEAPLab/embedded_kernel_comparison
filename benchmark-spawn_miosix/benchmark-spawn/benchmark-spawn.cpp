#include <cstdio>
#include <cstdlib>
#include <spawn.h>
#include <sys/wait.h>
#include "benchmark.h"

void usage(const char *name)
{
    fiprintf(stderr, "usage: %s [count]\n", name);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc > 2)
        usage(argv[0]);
    unsigned int count = 100;
    if (argc == 2) {
        int n = siscanf(argv[1], "%u", &count);
        if (n != 1)
            usage(argv[0]);
    }

    BEGIN_BENCHMARK("spawn", count);
    pid_t pid;
    char fn[] = "/bin/child";
    char *const argv[] = { fn, nullptr };
    char *const envp[] = { nullptr };
    int err = posix_spawn(&pid, fn, nullptr, nullptr, argv, envp);
    if (err) {
        fiprintf(stderr, "fatal: posix_spawn failed with code %d (count=%u)\n", err, i);
        exit(1);
    }
    waitpid(pid, nullptr, 0);
    END_BENCHMARK;
}
