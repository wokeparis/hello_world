/*************************************************************************
	> File Name: libevent_sample2_client.c
	> Author: 
	> Mail: 
	> Created Time: Thu 12 Dec 2019 01:22:34 AM PST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <netinet/tcp.h>

int main()
{
    int length = 800;
    char* mesg = (char*)malloc((length+1)*sizeof(char));
    if(mesg == NULL)
        exit(1);
    int i;
    for(i = 0; i < length; i++)
        strcat(mesg, "a");

    int port = 9876;
    struct sockaddr_in my_address;
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = htonl(0x7f000001);
    my_address.sin_port = htons(port);

    struct event_base* base = event_base_new();
    evutil_socket_t fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct bufferevent* conn = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    int enable = 1;
    if(setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable)) < 0)
        printf("error : TCP_NODELAY setting error\n")
    bufferevent_enable(conn, EV_WRITE);
    if(bufferevent_socket_connect(conn, (struct sockaddr*)&my_address, sizeof(my_address)) == 0)
        printf("connect success\n");
    bufferevent_write(conn, mesg, length);
    struct evbuffer* output = bufferevent_get_output(conn);
    int len = 0;
    len = evbuffer_get_length(output);

    event_base_dispatch(base);
    event_base_free(base);

    return 0;
}
