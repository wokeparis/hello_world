#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "zmq.h"
#include <thread>

using namespace std;

#define TRUE 1

void Recv(void* arg)
{
    while(TRUE)
    {
        void* socket = arg;
        printf("into while\n");
        char szBuf[1024] = {0};
        int ret = zmq_recv(socket, szBuf, sizeof(szBuf) - 1, 0);
        if (ret > 0)
        {
            printf("Recv:%s\n", szBuf);
        }
    }
}


void Recv2(void* arg)
{
    while(TRUE)
    {
        void* socket = arg;
        printf("into while\n");
        char szBuf[1024] = {0};
        int ret = zmq_recv(socket, szBuf, sizeof(szBuf) - 1, 0);
        if (ret > 0)
        {
            printf("Recv2:%s\n", szBuf);
        }
    }
}

int main()
{
    printf("Hello world!\n");

    void* context = zmq_ctx_new();
    assert(context != NULL);

    void* socket = zmq_socket(context, ZMQ_SUB);
    assert(socket != NULL);

    int ret = zmq_connect(socket, "tcp://localhost:5555");
    assert(ret == 0);

    ret = zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);
    assert(ret == 0);
    thread t1(Recv,socket);
    thread t2(Recv2,socket);
    /*
    while(1)
    {
    printf("into while\n");
    char szBuf[1024] = {0};
    ret = zmq_recv(socket, szBuf, sizeof(szBuf) - 1, 0);
    if (ret > 0)
    {
    printf("%s\n", szBuf);
    }
    }
    */
    t1.join();
    t2.join();
    zmq_close(socket);
    zmq_ctx_destroy(context);

    return 0;
}