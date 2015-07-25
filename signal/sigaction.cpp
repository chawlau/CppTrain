#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
int g_iSeq = 0;
void SignHandlerNew(int iSignNo,siginfo_t *pInfo,void *pReserved)
{
    int iSeq = g_iSeq++;
    printf("%d Enter SignHandlerNew,signo:%d\n",iSeq,iSignNo);
    sleep(3);
    printf("%d Leave SignHandlerNew,signo:%d\n",iSeq,iSignNo);
}
int main()
{
    struct sigaction act;
    act.sa_sigaction = SignHandlerNew;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
