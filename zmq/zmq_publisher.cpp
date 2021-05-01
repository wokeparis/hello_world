#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "zmq.h"

int main()
{
    void* context = zmq_ctx_new();
    assert(context != NULL);

    void* socket = zmq_socket(context, ZMQ_PUB);
    assert(socket != NULL);

    int ret = zmq_bind(socket, "tcp://*:5555");
    assert(ret == 0);

    int i = 0;
    while(1)
    {
        char szBuf[1024] = {0};
        snprintf(szBuf, sizeof(szBuf), "server i=%d", i);
        ret = zmq_send(socket, szBuf, strlen(szBuf) + 1, 0);
        i++;
    }

    zmq_close (socket);
    zmq_ctx_destroy (context);

    return 0;
}