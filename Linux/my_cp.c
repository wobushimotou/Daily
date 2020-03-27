#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int fd = open(argv[1],O_RDONLY);
    
    if(fd == -1) {
        printf("源文件不存在\n");
        return 0;
    }

    int nfd;    
    struct stat buf;

    int ret = lstat(argv[2],&buf);

    if(ret == -1) {
        nfd = open(argv[2],O_CREAT|O_RDWR,0777);
    }
    else {
        char filename[100];
        bzero(filename,100);
        strcpy(filename,argv[2]);
        printf("%s\n",filename);
        if(filename[strlen(filename)-1] != '/')
            filename[strlen(filename)] = '/'; 

        printf("%s\n",filename);

        strcat(filename,argv[1]);
        printf("%s\n",filename);

        nfd = open(filename,O_CREAT|O_RDWR,0777);
    }  

    char ch;

    while(read(fd,&ch,1)) {
        write(nfd,&ch,1);
    }

    close(fd);
    close(nfd);

    return 0;
}

