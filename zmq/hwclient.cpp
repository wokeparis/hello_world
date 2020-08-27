/*************************************************************************
	> File Name: hwclient.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 26 Dec 2019 10:25:48 PM PST
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(void)
{
    void * context = zmq_init(1);
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");
    int request_nbr;
    for(request_nbr = 0; request_nbr != 10; request_nbr++)
    {
        zmq_msg_t request;
        zmq_msg_init_size(&request, 5);
        memcpy(zmq_msg_data(&request), "hello", 5);
        zmq_send(requester, &request, 0);
        zmq_msg_close(&request);

        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_recv(requester, &reply, 0);
        zmq_msg_close(&reply);
    }
    zmq_close(requester);
    zmq_term(context);
    return 0;
}
