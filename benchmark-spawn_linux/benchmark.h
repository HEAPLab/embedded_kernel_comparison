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
        gettimeofday(&stime,NULL);
    }
    
    uint64_t end()
    {
        struct timeval etime;
        gettimeofday(&etime,NULL);
        uint64_t start=static_cast<uint64_t>(stime.tv_usec)+static_cast<uint64_t>(stime.tv_sec)*1000000ULL;
        uint64_t end=static_cast<uint64_t>(etime.tv_usec)+static_cast<uint64_t>(etime.tv_sec)*1000000ULL;
        uint64_t dt = end-start;
        return dt*1000; //us to ns
    }
private:
    struct timeval stime;
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

