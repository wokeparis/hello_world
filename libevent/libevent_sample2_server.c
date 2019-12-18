/*************************************************************************
	> File Name: libevent_sample2_server.c
	> Author: 
	> Mail: 
	> Created Time: Wed 11 Dec 2019 07:43:22 AM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <netinet/tcp.h>

static void server_on_read(struct bufferevent* bev,void* arg)
{
    struct timeval start_t;
    gettimeofday(&start_t,NULL);
    printf("Warning: server_on_read start timestamp  %lu.%06lu\n", start_t.tv_sec, start_t.tv_usec);
 
    struct evbuffer* input = bufferevent_get_input(bev);
    size_t len = 0;
    len = evbuffer_get_length(input);
    printf("There Is %u Bytes Data In The Buffer In Total.\n",
            (unsigned)len);
    
    // read
    char* buf;
    buf = (char*)malloc(sizeof(char)*len);
    if(NULL==buf){return;}
    //evbuffer_copyout(input,buf,len); // it do not clear the input buffer
    evbuffer_remove(input,buf,len); // clear the buffer
    printf("Server gets the message from client: %s\n", buf);    
   
    // check
    len = 0;
    len = evbuffer_get_length(input);
    printf("After the first reading, there Is %u Bytes Data Left In The Buffer.\n",
            (unsigned)len);
    
    free(buf);
    buf=NULL;
    return;
}


void server_on_accept(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr * address, int socklen, void *arg)
{
    printf("accept a client : %d\n", fd);

    int enable = 1;
    if(setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable)) < 0)
        printf("Consensus-side: TCP_NODELAY SETTING ERROR!\n");

    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent* new_buff_event = bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(new_buff_event, server_on_read,NULL,NULL,NULL);
    bufferevent_enable(new_buff_event, EV_READ|EV_WRITE);

}


int main()
{
    int port = 9876;
    struct sockaddr_in my_address;
    memset(&my_address, 0, sizeof(my_address));
    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = htonl(0x7f000001);//127.0.0.1
    my_address.sin_port = htons(port);

    struct event_base *base = event_base_new();
    struct evconnlistener* listener = evconnlisterer_new_bind(base,server_on_accept,NULL,LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSERABLE,-1, (struct sockaddr*)&my_address.sizeof(my_address));
    if(!listener)
       exit(1);
    

    event_base_dispatch(base);
    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}


