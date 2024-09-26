 /***************************************************************************
  *   Copyright (C) 2024 by Terraneo Federico                               *
  *                                                                         *
  *   This program is free software; you can redistribute it and/or modify  *
  *   it under the terms of the GNU General Public License as published by  *
  *   the Free Software Foundation; either version 2 of the License, or     *
  *   (at your option) any later version.                                   *
  *                                                                         *
  *   This program is distributed in the hope that it will be useful,       *
  *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
  *   GNU General Public License for more details.                          *
  *                                                                         *
  *   You should have received a copy of the GNU General Public License     *
  *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
  ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//Addresses for stm32f469i-disco
char *ptr=(char*)0xc0000000;     //Pointer to external RAM base address
unsigned int size=16*1024*1024;  //Size of external RAM
//Addresses for stm32f4discovery
// char *ptr=(char*)0x20000000; //Pointer to RAM base address
// unsigned int size=128*1024;  //Size of RAM

void fuzzpointers()
{
    puts("Fuzzing pointers");
    //This test works as follows. A pointer is taken to the first byte of the
    //board RAM memory, something that can be easily gathered from the chip
    //programmer manual, and then the memset function is used to fill the entire
    //RAM memory with zeros. If the OS has memory protection, the fuzzer process
    //will segfault before it had the chance to write a single byte, preserving
    //system integrity. If the OS memory protection is broken/missing, this
    //program will cause a denial-of-service (DoS) attack crashing the kernel.
    //Failing this test demonstrates that a process has arbitrary memory write
    //capability, and is a proxy to demonstrate the possibility of implementing
    //kernel-level exploits.

    memset(ptr,0,size);
}

void fuzzsyscalls()
{
    puts("Fuzzing syscalls");
    //This test works as follows. It calls certain syscalls that write to a
    //user-supplied pointer, passing a pointer outside the address space of the
    //process. If the kernel correctly validates pointers passed to syscalls,
    //then it will refuse to perform the syscall. If it does not, then this
    //opens up the possibility for a process to make writes to arbitrary memory
    //locations. This is here demonstrated with a denial of service attack (Dos)
    //by crashing the kernel, but is a proxy to demonstrate the possibility of
    //implementing kernel-level exploits.
    
    int fd=open("/dev/zero",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        puts("Test failed because can't open /dev/zero");
        return;
    }
    
    int nread=read(fd,ptr,size);
    if(nread<0)
    {
        perror("read");
        puts("Test passed: the OS refused to write to a pointer outside process");
        return;
    }
}

void fuzzopcodes()
{
    puts("Fuzzing opcodes");
    //This test works as follows. It inserts an illegal opcode in the code flow.
    //If the kernel correctly implements the abstraction of processes, only
    //the process will be segfaulted, otherwise this is another possibility for
    //a denial of service (DoS) attack crashing the entire kernel.
    
    asm volatile(".word 0xffffffff");
}

void fuzzbreakpoint()
{
    puts("Fuzzing breakpoint");
    //This test works as follows. The process executes a breakpoint instruction.
    //If the kernel does not trap this instruction while a debugger is not
    //connected, it has the possibility to lock the entire CPU, causing a denial
    //of service (DoS).
    
    asm volatile("bkpt");
}

int main(int argc, char *argv[])
{
    int fuzzoption;
    if(argc==2) fuzzoption=atoi(argv[1]);
    else {
        puts("What do you want to fuzz?");
        puts("1 : out of bound pointers");
        puts("2 : syscalls");
        puts("3 : illegal instructions");
        puts("4 : breakpoint instruction");
        fuzzoption=getchar()-'0';
    }
    switch(fuzzoption)
    {
        case 1: fuzzpointers(); break;
        case 2: fuzzsyscalls(); break;
        case 3: fuzzopcodes(); break;
        case 4: fuzzbreakpoint(); break;
        default:
            puts("wrong option selected");
            return 1;
    }
    return 0;
}
