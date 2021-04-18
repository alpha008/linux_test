#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc ,char*argv[]){
    if(argc !=2 )
        exit(0);
    printf("pid=%d\n",getpid());
    size_t mb = strtoul(argv[1],NULL,0);
    size_t nbytes = mb*0x100000;
    char *ptr = (char *)malloc(nbytes);
    if(ptr == NULL){
        perror("malloc");
        exit("EXIT_FAILURE");
    }
   // memset(ptr,0,nbytes);

    printf("allocated %d mb \n",mb);
    pause();
    free(ptr);

    return 0;
}


/*
cat /proc/30018/status


初始化为0之后
VmPeak:	    5544 kB
VmSize:	    5544 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	    2508 kB
VmRSS:	    2508 kB
RssAnon:	    1064 kB
RssFile:	    1444 kB
RssShmem:	       0 kB
VmData:	    1204 kB
VmStk:	     132 kB
VmExe:	       4 kB
VmLib:	    2120 kB
VmPTE:	      56 kB
VmSwap:	       0 kB


申请后但是没有使用
VmPeak:	    5544 kB
VmSize:	    5544 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	     748 kB
VmRSS:	     748 kB
RssAnon:	      64 kB
RssFile:	     684 kB
RssShmem:	       0 kB

*/