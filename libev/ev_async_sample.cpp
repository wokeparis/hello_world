#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ev.h>

ev_async async_watcher;

static void sigint_callback(struct ev_loop *loop,ev_signal * w,int revents)
{
    if(revents & EV_SIGNAL)
    {
        printf("Call sigint_callback\n");
        printf("ev_async_send 调用前 %d\n",ev_async_pending(&async_watcher));
        ev_async_send(loop,&async_watcher);//这里会调用async_callback
        printf("ev_async_send 调用后 %d\n",ev_async_pending(&async_watcher));
    }
}

static void sigquit_callback(struct ev_loop *loop,ev_signal *w,int revetns)
{
    printf("Call sigquit_callback\n");
    ev_break(loop,EVBREAK_ALL);
}

static void async_callback(struct ev_loop *loop,ev_async *w,int revents)
{
    if(revents & EV_ASYNC)
    {
        printf("Call async_callback\n");
    }
}

int main(int argc, char **args)
{
    struct ev_loop *main_loop=ev_default_loop(0);

    ev_init(&async_watcher,async_callback);
    ev_async_start(main_loop,&async_watcher);

    ev_signal sigint_watcher;
    ev_init(&sigint_watcher,sigint_callback);
    ev_signal_set(&sigint_watcher,SIGINT);
    ev_signal_start(main_loop,&sigint_watcher);

    ev_signal sigquit_watcher;//这里的ev_signal不能与上面共用,必须在声明一个变量
    ev_init(&sigquit_watcher,sigquit_callback);
    ev_signal_set(&sigquit_watcher,SIGQUIT);
    ev_signal_start(main_loop,&sigquit_watcher);

    ev_run(main_loop,0);
    return 0;
}