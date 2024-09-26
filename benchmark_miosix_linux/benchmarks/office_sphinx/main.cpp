#include <cstdio>
#include <unistd.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int sphinx_main(int argc, const char *argv[]);

/*
../src/examples/sphinx2-continuous -adcin TRUE -adcext 16k -ctloffset 0 -ctlcount 100000000 -agcmax FALSE -langwt 6.5 -fwdflatlw 8.5 -rescorelw 9.5 -ugwt 0.5 -fillpen 1e-10 -silpen 0.005 -inspen 0.65 -top 1 -topsenfrm 3 -topsenthresh -70000 -beam 2e-06 -npbeam 2e-06 -lpbeam 2e-05 -lponlybeam 0.0005 -nwbeam 0.0005 -fwdflat FALSE -fwdflatbeam 1e-08 -fwdflatnwbeam 0.0003 -bestpath TRUE -kbdumpdir ../model/lm/turtle -lmfn ../model/lm/turtle/turtle.lm -dictfn ../model/lm/turtle/turtle.dic -noisedict ../model/hmm/6k/noisedict -phnfn ../model/hmm/6k/phone -mapfn ../model/hmm/6k/map -hmmdir ../model/hmm/6k -hmmdirlist ../model/hmm/6k -8bsen TRUE -sendumpfn ../model/hmm/6k/sendump -cbdir ../model/hmm/6k -matchfn FOO -ctlfn bigtest.ctl -datadir ./ -verbose 10
*/

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
//     puts("type enter");
//     getchar();

    chdir("/sd/mibench_files/sphinx");
    
    const char *arg0[] = {"", "-adcin", "TRUE", "-adcext", "16k", "-ctloffset", "0", "-ctlcount", "100000000", "-agcmax", "FALSE", "-langwt", "6.5", "-fwdflatlw", "8.5", "-rescorelw", "9.5", "-ugwt", "0.5", "-fillpen", "1e-10", "-silpen", "0.005", "-inspen", "0.65", "-top", "1", "-topsenfrm", "3", "-topsenthresh", "-70000", "-beam", "2e-06", "-npbeam", "2e-06", "-lpbeam", "2e-05", "-lponlybeam", "0.0005", "-nwbeam", "0.0005", "-fwdflat", "FALSE", "-fwdflatbeam", "1e-08", "-fwdflatnwbeam", "0.0003", "-bestpath", "TRUE", "-kbdumpdir", "model/lm/turtle", "-lmfn", "model/lm/turtle/turtle.lm", "-dictfn", "model/lm/turtle/turtle.dic", "-noisedict", "model/hmm/6k/noisedict", "-phnfn", "model/hmm/6k/phone", "-mapfn", "model/hmm/6k/map", "-hmmdir", "model/hmm/6k", "-hmmdirlist", "model/hmm/6k", "-8bsen", "TRUE", "-sendumpfn", "model/hmm/6k/sendump", "-cbdir", "model/hmm/6k", "-matchfn", "FOO", "-ctlfn", "test.ctl", "-datadir", "./", "-verbose", "10", NULL};

    BEGIN_SMALL_BENCHMARK("sphinx small");
    sphinx_main(79, arg0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    const char *arg1[] = {"", "-adcin", "TRUE", "-adcext", "16k", "-ctloffset", "0", "-ctlcount", "100000000", "-agcmax", "FALSE", "-langwt", "6.5", "-fwdflatlw", "8.5", "-rescorelw", "9.5", "-ugwt", "0.5", "-fillpen", "1e-10", "-silpen", "0.005", "-inspen", "0.65", "-top", "1", "-topsenfrm", "3", "-topsenthresh", "-70000", "-beam", "2e-06", "-npbeam", "2e-06", "-lpbeam", "2e-05", "-lponlybeam", "0.0005", "-nwbeam", "0.0005", "-fwdflat", "FALSE", "-fwdflatbeam", "1e-08", "-fwdflatnwbeam", "0.0003", "-bestpath", "TRUE", "-kbdumpdir", "../model/lm/turtle", "-lmfn", "model/lm/turtle/turtle.lm", "-dictfn", "model/lm/turtle/turtle.dic", "-noisedict", "model/hmm/6k/noisedict", "-phnfn", "model/hmm/6k/phone", "-mapfn", "model/hmm/6k/map", "-hmmdir", "model/hmm/6k", "-hmmdirlist", "model/hmm/6k", "-8bsen", "TRUE", "-sendumpfn", "model/hmm/6k/sendump", "-cbdir", "model/hmm/6k", "-matchfn", "bigFOO", "-ctlfn", "bigtest.ctl", "-datadir", "./", "-verbose", "10", NULL};

    BEGIN_LARGE_BENCHMARK("sphinx large");
    sphinx_main(79, arg1);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
