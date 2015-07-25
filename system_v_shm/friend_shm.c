#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>  //头文件包含
#include <sys/types.h>
int main()
{
    key_t key = ftok("b.dat",1);					//1. 写入端先用ftok函数获得key
    if(key == -1)
    {
        perror("ftok");
        exit(-1);
    }
    int shmid = shmget(key,4096,IPC_CREAT); 	//2. 写入端用shmget函数创建一共享内存段
    if(shmid == -1)
    {
        perror("shmget");
        exit(-1);
    }
    char *pMap = (char *)shmat(shmid, NULL, 0);	//3. 获得共享内存段的首地址
    memset(pMap, 0, 4096);
    memcpy(pMap, "hello world", 4096);			//4. 往共享内存段中写入内容
    if(shmdt(pMap) == -1)						//5. 关闭共享内存段
    {
        perror("shmdt");
        exit(-1);
    }
}
