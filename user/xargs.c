#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int getInput(char buff[100])
{
    gets(buff, 100);
    
    if(buff[0] == 0)
        return 1;

    return 0;
}

int main(int argc, char *argv[])
{
    char buff[MAXARG][100];

    int inputCount = 0;
    int pid = 0;

    while(getInput(buff[inputCount]) == 0)
    {
        inputCount++;
    }
    
    for(int i = 0; i < inputCount; i++)
    {
        char *command[MAXARG];

        for(int j = 1; j < argc; j++)
        {
            command[j-1] = argv[j];
        }

        command[argc - 1] = buff[i];
        command[argc - 1][strlen(command[argc - 1]) - 1] = 0;

        if(fork() == 0)
        {
            exec(command[0], command);
        }

        wait(&pid);
    }
    
    exit(0);
}