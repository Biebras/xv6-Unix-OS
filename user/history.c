#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void display(int fd, int num)
{
	//command count
	int count = 0;
	//history file contents
	char output[512];
	char commands[100][20];
	//size of output
	int size = sizeof(output) / sizeof(output[0]);
	//last commands index start.
	int lastCommandStart = 0;

	//read output file and store contents to output
	while(read(fd, output, size)) {}

	//loop through output
	for(int i = 0; i < size - 1; i++)
	{
		//if current and next symbol is null, then we read all commands
		if(output[i] == 0 && output[i+1] == 0)
			break;
		
		//put command into command array
		commands[count][i - lastCommandStart] = output[i];

		//if current symbol is null, then it's the end of command
		if(output[i] == 0)
        {   
			//increase command number
            count++;
			//set new command start
            lastCommandStart = i + 1;
        }
	}

	//set num to max if there is need, so it would show all history
	if(num <= 0 || num > count)
		num = count;

	//iterate through commands and print them
	for(int i = count - num; i < count + 1; i++)
	{
		printf("%d: %s", i, commands[i]);
	}
}

int main(int argc, char *argv[])
{
    int fd;

    printf("======History======\n");

    if((fd = open("cmdLog", 0)) < 0)
    {
        printf("error: Can't read history");
        exit(1);
    }

    if(argc == 1)
	{
		display(fd, 0);
	}
	else
	{
		display(fd, atoi(argv[1]));
	}

	close(fd);
    exit(0);
}
