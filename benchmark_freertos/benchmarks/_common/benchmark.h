#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "FreeRTOS.h"
#include "task.h"


#define BENCH_ALWAYS_INLINE static inline __attribute__((always_inline))

#define USE_REGISTER(x) asm volatile("" : "+r"(x) : :)

BENCH_ALWAYS_INLINE void use(void *value)
{
    asm volatile("" : : "r,m"(value) : "memory");
}


#ifdef MIBENCH_NO_SMALL
#define BEGIN_SMALL_BENCHMARK(name) \
    do { if (0) { \
        fiprintf(stderr, "[FreeRTOS MiBench] '%s' start\n", name); \
        static const char *_benchName = name; \
        int _t0 = xTaskGetTickCount()
#else
#define BEGIN_SMALL_BENCHMARK(name) \
    do { if (1) { \
        fiprintf(stderr, "[FreeRTOS MiBench] '%s' start\n", name); \
        static const char *_benchName = name; \
        int _t0 = xTaskGetTickCount()
#endif

#ifdef MIBENCH_NO_LARGE
#define BEGIN_LARGE_BENCHMARK(name) \
    do { if (0) { \
        fiprintf(stderr, "[FreeRTOS MiBench] '%s' start\n", name); \
        static const char *_benchName = name; \
        int _t0 = xTaskGetTickCount()
#else
#define BEGIN_LARGE_BENCHMARK(name) \
    do { if (1) { \
        fiprintf(stderr, "[FreeRTOS MiBench] '%s' start\n", name); \
        static const char *_benchName = name; \
        int _t0 = xTaskGetTickCount()
#endif

#define END_BENCHMARK \
        int _dt = xTaskGetTickCount() - _t0; \
        fiprintf(stderr, "[FreeRTOS MiBench] '%s' end, time = %d\n", _benchName, _dt); \
    } } while (0)

#endif
