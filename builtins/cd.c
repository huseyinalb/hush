#include "cd.h"

int cd(char** args)
{
    if(chdir(args[1]))
    {
        return 1;
    }
    return 0;
}