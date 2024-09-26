#include <cstdio>
#include <benchmark.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#ifndef MIBENCH_PROCESS_MODE
#include "miosix.h"
#include "kernel/process.h"
#include "filesystem/gpio/gpiodev.h"
using namespace miosix;
#endif

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    iprintf("Adding GPIO to devfs\n");
    FilesystemManager& fsm=FilesystemManager::instance();
    auto gpio = intrusive_ref_ptr<Device>(new GPIODevice());
    bool ok = fsm.getDevFs()->addDevice("gpio0", gpio);
    iprintf("DevFs::addDevice() returned %d\n", (int)ok);
    #endif

    BEGIN_SMALL_BENCHMARK("blinker");

    iprintf("Blinker\n");
    int fd = open("/dev/gpio0", O_RDWR);
    if (fd > 0) {
        iprintf("/dev/gpio opened successfully (fd = %d)\n", fd);
    } else {
        perror("could not open /dev/gpio");
        return 1;
    }

    char param = 0;

    for (int i=0; i<2; i++) {
        iprintf("on\n");
        int res;
        res = write(fd, &param, 1);
        if (res == -1)
            perror("on failed");
        sleep(1);
        iprintf("off\n");
        res = read(fd, &param, 1);
        if (res == -1)
            perror("off failed");
        sleep(1);
    }

    for (;;) {
        write(fd, &param, 1);
        read(fd, &param, 1);
    }

    close(fd);
    iprintf("Test done, bye!\n");

    END_BENCHMARK;
    return 0;
}
