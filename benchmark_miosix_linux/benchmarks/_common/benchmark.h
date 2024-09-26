#pragma once

#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#else
#include <sys/ioctl.h>
#endif

#ifdef MIBENCH_LINUX
#define iprintf printf
#define fiprintf fprintf
#endif

//#define MIOSIX_NATIVE_TIMER


#define BENCH_ALWAYS_INLINE static inline __attribute__((always_inline))

#define USE_REGISTER(x) asm volatile("" : "+r"(x) : :)

BENCH_ALWAYS_INLINE void use(void *value)
{
    asm volatile("" : : "r,m"(value) : "memory");
}


#if defined(MIBENCH_PROCESS_MODE) && !defined(MIBENCH_LINUX)
extern "C" unsigned int getMaxHeap();
#endif


#if defined(MIBENCH_LINUX)
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
#elif !defined(MIBENCH_PROCESS_MODE) && defined(MIOSIX_NATIVE_TIMER)
class BenchmarkTimer
{
public:
    void start()
    {
        t0 = miosix::getTime();
    }
    
    uint64_t end()
    {
        long long t1 = miosix::getTime();
        return t1-t0;
    }
private:
    long long t0;
};
#else
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
#endif


#ifdef MIBENCH_NO_PROFILING
class BenchmarkStats
{
public:
    inline BenchmarkStats(const char *name) {}
};
#else
class BenchmarkStats
{
public:
    inline BenchmarkStats(const char *name) : name(name)
    {
        saveInitialMemoryStats();
        fiprintf(stderr, "[Miosix MiBench] '%s' start\n", name);
        #ifdef MIBENCH_PROCESS_MODE
        ioctl(0, 0, NULL); // HACK for resetting I/O traffic counters
        #endif
        timer.start();
    }

    inline ~BenchmarkStats()
    {
        uint64_t dt = timer.end();
        #ifdef MIBENCH_PROCESS_MODE
        ioctl(1, 0, NULL); // HACK for printing I/O traffic counters since last reset
        #endif
        fiprintf(stderr, "[Miosix MiBench] '%s' end, time = %" PRIu64 " ns\n", name, dt);
        printMemoryStats();
    }

private:
    void saveInitialMemoryStats()
    {
        #ifndef MIBENCH_PROCESS_MODE
        initialFreeHeap = miosix::MemoryProfiling::getCurrentFreeHeap();
        #else
        #ifndef MIBENCH_LINUX
        fiprintf(stderr, "[Miosix MiBench] '%s' max heap (pre) = %u B\n", name, getMaxHeap());
        #endif
        #endif
    }

    void printMemoryStats()
    {
        #ifndef MIBENCH_PROCESS_MODE
        unsigned int minFreeStack = miosix::MemoryProfiling::getAbsoluteFreeStack();
        unsigned int stackSize = miosix::MemoryProfiling::getStackSize();
        unsigned int minFreeHeap = miosix::MemoryProfiling::getAbsoluteFreeHeap();
        unsigned int heapSize = miosix::MemoryProfiling::getHeapSize();
        fiprintf(stderr, "[Miosix MiBench] '%s' stack usage = %u B\n", name, stackSize-minFreeStack);
        fiprintf(stderr, "[Miosix MiBench] '%s' heap usage = %u B\n", name, heapSize-minFreeHeap);

        unsigned int curFreeHeap = miosix::MemoryProfiling::getCurrentFreeHeap();
        fiprintf(stderr, "[Miosix MiBench] '%s' heap potential leak = %d B\n", name, (int)initialFreeHeap-(int)curFreeHeap);
        #else
        #ifndef MIBENCH_LINUX
        fiprintf(stderr, "[Miosix MiBench] '%s' max heap (post) = %u B\n", name, getMaxHeap());
        #endif
        #endif
    }

    BenchmarkTimer timer;
    const char *name;
    #ifndef MIBENCH_PROCESS_MODE
    unsigned int initialFreeHeap;
    #endif
};
#endif

//Uncomment to enable a sync() before and after each benchmark
//#define WITH_SYNC

#ifdef WITH_SYNC
#define DOSYNC sync();
#else
#define DOSYNC
#endif


#ifdef MIBENCH_NO_SMALL
#define BEGIN_SMALL_BENCHMARK(name) do { if (0) { DOSYNC BenchmarkStats _stats(name)
#else
#define BEGIN_SMALL_BENCHMARK(name) do { if (1) { DOSYNC BenchmarkStats _stats(name)
#endif

#ifdef MIBENCH_NO_LARGE
#define BEGIN_LARGE_BENCHMARK(name) do { if (0) { DOSYNC BenchmarkStats _stats(name)
#else
#define BEGIN_LARGE_BENCHMARK(name) do { if (1) { DOSYNC BenchmarkStats _stats(name)
#endif

#define END_BENCHMARK DOSYNC } } while (0)

