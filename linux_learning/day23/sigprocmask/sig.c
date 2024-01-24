#include <func.h>

int main(int argc, char const *argv[])
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);

    sigprocmask(SIG_BLOCK,&mask,NULL);
    printf("SIGINT is blocked, sleeping for 5 seconds\n");
    sleep(5);
    printf("Waking up, unblocking SIGINT\n");

    sigprocmask(SIG_UNBLOCK,&mask,NULL);

    return 0;
}
