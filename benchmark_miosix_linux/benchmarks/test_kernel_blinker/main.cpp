#include <cstdio>
#include <benchmark.h>
#include "kernel/process.h"
#include "miosix.h"

using namespace miosix;

using port = Gpio<GPIOC_BASE,6>;

int main()
{
    BEGIN_SMALL_BENCHMARK("blinker");

    iprintf("Blinker Kernel\n");

    port::mode(Mode::OUTPUT);
    port::speed(Speed::VERY_HIGH);

    for (int i=0; i<2; i++) {
        port::high();
        sleep(1);
        port::low();
        sleep(1);
    }

    for (;;) {
        port::high();
        port::low();
        port::high();
        port::low();
        port::high();
        port::low();
        port::high();
        port::low();
        port::high();
        port::low();
        port::high();
        port::low();
        port::high();
        port::low();
    }

    END_BENCHMARK;
    return 0;
}
