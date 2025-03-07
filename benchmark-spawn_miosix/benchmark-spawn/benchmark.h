#pragma once

#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define iprintf printf
#define fiprintf fprintf


class BenchmarkTimer
{
public:
    void start()
    {
        clock_gettime(CLOCK_MONOTONIC, &stime);
    }
    
    uint64_t end()
    {
        struct timespec etime;
        clock_gettime(CLOCK_MONOTONIC, &etime);
        uint64_t t0 = stime.tv_nsec + stime.tv_sec * (uint64_t)1000000000;
        uint64_t t1 = etime.tv_nsec + etime.tv_sec * (uint64_t)1000000000;
        return t1-t0;
    }
private:
    struct timespec stime;
};


class BenchmarkStats
{
public:
    inline BenchmarkStats(const char *name, uint64_t rounds) : name(name), rounds(rounds)
    {
        fiprintf(stderr, "'%s' start\n", name);
        timer.start();
    }

    inline ~BenchmarkStats()
    {
        uint64_t dt = timer.end();
        dt /= rounds;
        fiprintf(stderr, "'%s' end %" PRIu64 " rounds, time = %" PRIu64 " ns\n", name, rounds, dt);
    }

private:
    BenchmarkTimer timer;
    const char *name;
    uint64_t rounds;
};


#define BEGIN_BENCHMARK(name, rounds) \
  do { \
    BenchmarkStats _stats((name), (rounds)); \
    for (unsigned int i=0; i<(rounds); i++) {

#define END_BENCHMARK \
    } \
  } while (0)

