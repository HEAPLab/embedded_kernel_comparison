#include <cstdio>
#include <sys/wait.h>
#include <signal.h>
#include <string>
#include <vector>
#include "miosix.h"
#include "kernel/process.h"
#include "filesystem/gpio/gpiodev.h"

using namespace std;
using namespace miosix;

void findElfs(const char *where, vector<string>& res)
{
    DIR *d = opendir(where);
    if (!d) {
        printf("Where's the forest!? Can't find it\n");
        return;
    }
    struct dirent *dent = readdir(d);
    while (dent) {
        if (dent->d_type == DT_REG) {
            int l = strlen(dent->d_name);
            if (l >= 5) {
                if (strcmp(dent->d_name + l - 4, ".elf") == 0) {
                    iprintf("Found an elf! %s\n", dent->d_name);
                    string s(where);
                    s += "/";
                    s += dent->d_name;
                    res.push_back(s);
                }
            }
        }
        dent = readdir(d);
    }
    closedir(d);
}

int main()
{
    const int nRuns = 3;

    iprintf("Adding GPIO to devfs\n");
    FilesystemManager& fsm=FilesystemManager::instance();
    auto gpio = intrusive_ref_ptr<Device>(new GPIODevice());
    bool ok = fsm.getDevFs()->addDevice("gpio0", gpio);
    iprintf("DevFs::addDevice() returned %d\n", (int)ok);

    vector<string> elfs;
    iprintf("Searching for elfs...\n");
    findElfs("/bin", elfs);
    for (string& path: elfs) {
        const char *fp = path.c_str();
        for (int i=0; i<nRuns; i++) {
            iprintf("Running %s\n", fp);
            Process::spawn(fp);
            int ec;
            Process::wait(&ec);
            if (WIFEXITED(ec)) {
                iprintf("Exit code is %d\n", WEXITSTATUS(ec));
            } else if (WIFSIGNALED(ec)) {
                if (WTERMSIG(ec)==SIGSEGV)
                    iprintf("Process segfaulted\n");
                // else... what happens?
                break;
            }
        }
    }
    iprintf("\n*** FINISHED! ***\n");
    ledOn();
    for (int i=0; i<5; i++) {
        putchar('\a');
        sleep(1);
    }
}
