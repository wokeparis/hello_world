/*************************************************************************
	> File Name: someapi.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 26 Dec 2019 10:36:02 PM PST
 ************************************************************************/

#include<iostream>
//从zmq socket中接收字符串，并转换为C的字符串
static char*
s_recv(void *socket)
{
    zmq_msg_t message;
    zmq_msg_init(&message);
    zmq_recv(socket, &message, 0);
    int size = zmq_msg_size(&message);
    char *string = malloc(size+1);
    memcpy(string, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    string[size] = 0;
    return (string);
}
