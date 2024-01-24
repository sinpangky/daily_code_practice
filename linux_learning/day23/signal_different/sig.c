#include <func.h>

void sigfunc(int signum){
    printf("signal %d begin...\n",signum);
    sleep(3);
    printf("signal %d end.\n",signum);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT,sigfunc);
    signal(SIGQUIT,sigfunc);
    while (1);
    
    return 0;
}
