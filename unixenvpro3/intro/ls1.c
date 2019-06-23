#include "apue.h"
#include <dirent.h>
int main(int argc, char *argv[])
{
	DIR			    *dp;
	struct dirent   *dirp;
    
	if (argc != 2)
		err_quit("usage: ls directory_name");
/*
opendir  此函数返回类似文件描述符
*/
	if ((dp = opendir(argv[1])) == NULL)
    {
        err_sys("can't open %s", argv[1]);
    }   
/*
readdir  读取当前文件描述符指向的文件名字
*/		
	while ((dirp = readdir(dp)) != NULL)
    {
        printf("%s\n", dirp->d_name);
    }   
	closedir(dp);
	exit(0);
}
