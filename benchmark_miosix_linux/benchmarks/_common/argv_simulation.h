#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>

// Writing this class was a mistake and reminded me why I hate C++ and it's a
// horrible language

struct WritableArguments
{
    WritableArguments()
    {
        argc = 0;
        argv = NULL;
    }

    // = operator is NOT syntactic sugar for copy constructor (thank you C++
    // for having a number of ways to construct an object that rivals the number
    // of stars in the universe)
    //   Hopefully the C++ standard committee won't invent more implicit
    // constructors in the future because the rules that determine if a class is
    // trivially copyable are EXTREMELY BAD. A class with a pointer member
    // should NOT be trivially copiable.
    //   Of course it needs to be for backcompat with C but that reinforces
    // the Fact (TM) that building an object oriented language on C was an
    // VERY VERY VERY BAD IDEA.
    WritableArguments(WritableArguments const &) = delete;
    WritableArguments& operator = (WritableArguments const &) = delete;
    WritableArguments(WritableArguments &&) = delete;
    WritableArguments & operator = (WritableArguments &&) = delete;

    WritableArguments(const char *orig[])
    {
        argc = 0;
        while (orig[argc]) argc++;
        argv = new char *[argc+1];
        if (!argv)
        {
            puts("allocation of argv buffer failed");
            exit(1);
        }
        int i;
        for (i=0; i<argc; i++) {
            char *ptr = strdup(orig[i]);
            if (!ptr)
            {
                puts("allocation of argument string buffer failed");
                exit(1);
            }
            argv[i] = ptr;
            origStrings.push_back(ptr);
        }
        argv[i] = NULL;
    }

    ~WritableArguments()
    {
        for (int i=0; i<origStrings.size(); i++)
            free(origStrings[i]);
        delete argv;
    }

    int argc;
    char **argv;
private:
    std::vector<char *> origStrings;
};
