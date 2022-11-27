#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *findName)
{
	char buf[512], *p;
	char skipDir1[2] = ".";
	char skipDir2[3] = "..";
	int fd;
	struct dirent de;
	struct stat st;
	
	//return error if can't open file
	if((fd = open(path, 0)) < 0)
	{
    	fprintf(2, "ls: cannot open %s\n", path);
		return;
	}
	
	//get stats of path  
	if(fstat(fd, &st) < 0)
	{
    	fprintf(2, "ls: cannot stat %s\n", path);
    	close(fd);
    	return;
	}
  
	switch(st.type)
	{
		//entering device
		case T_DEVICE:
		//entering file
		case T_FILE:
			printf("Find \n");
			break;
		
		//entering dir
		case T_DIR:
			//if the path is too long return
			if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
			{
				printf("ls: path too long\n");
				break;
			}
			
			//copy path to buffer
			strcpy(buf, path);
			//Why we doing this??????????????????????
			p = buf+strlen(buf);
			// Last character / ?????? i'm so confused with this
			*p++ = '/';

			while(read(fd, &de, sizeof(de)) == sizeof(de))
			{
				// HUH ????????????????????
      			if(de.inum == 0)
					continue;
				
				//move memory from de.name to p with size DIRSIZ
				memmove(p, de.name, DIRSIZ);
				//end char array with \0
				p[DIRSIZ] = 0;

				//if can't get stats from buffer return
				if(stat(buf, &st) < 0)
				{
					printf("ls: cannot stat %s\n", buf);
					continue;
				}
				
				//create new path
				char newPath[512];
				//move memory from path to new path
				memmove(newPath, path, DIRSIZ);
				//add '/'
				newPath[strlen(newPath)] = '/';
				//copy p to newPath after '/'
				memcpy(newPath + strlen(newPath), p, DIRSIZ);
				
				//directory logic execute here
				if(st.type == 1)
				{
					//if dir is '.' skip
					if(strcmp(p, skipDir1) == 0)
						continue;
					
					//if dir is '..' skip
					if(strcmp(p, skipDir2) == 0)
						continue;
					
					//if findName and p is the same print newPath
					if(strcmp(p, findName) == 0)
					{
						printf("%s\n", newPath);
					}
					
					//because current file is directory, search in it recurs.
					find(newPath, findName);
				}
				
				//file logic execute here
				if(st.type == 2)
				{
					//if p and findName is the same print newPath
					if(strcmp(p, findName) == 0)
					{
						printf("%s\n", newPath);
					}
				}
			}
		break;
	}
	close(fd);
}

int main(int argc, char *argv[])
{
    find(argv[1], argv[2]);
	exit(0);
}
