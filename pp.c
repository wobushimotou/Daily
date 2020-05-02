#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    DIR *dir;
    struct dirent *ddir;
    if((dir = opendir(".") ) == NULL) {
        printf("error\n");
    }
    while((ddir = readdir(dir))) {
        printf("%s ",ddir->d_name);
    }
    return 0;
}

