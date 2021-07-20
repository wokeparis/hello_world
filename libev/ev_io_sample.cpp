#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ev.h>


static void stdin_callback(struct ev_loop *loop,ev_io *w,int revents)
{
    char str[1024];
    if(revents & EV_READ)
    {
        //stdin might have data for us
        printf("有数据可读\n");
        scanf("%s",str);
        ev_io_stop(loop,w);
    }
    else if(revents & EV_WRITE)
    {
        //stdout might have data for us
        printf("有数据输出\n");
        //ev_break(loop,EVBREAK_ONE);
    }
    printf("water:%d\n",ev_is_active(w));
}

int main(int argc,char **argv)
{
    struct ev_loop * main_loop = ev_default_loop(0);
    //这里的ev_default_loop可以使用ev_loop_new动态分配一个，然后使用ev_loop_destroy销毁。
    //struct ev_loop * epoller = ev_loop_new(EVBACKEND_EPOLL | EVFLAG_NOENV);
    //这里一般是使用EVBACKEND_EPOLL模型，同样的还有EVBACKEND_SELECT EVBACKEND_POLL EVBACKEND_KQUEUE EVBACKEND_DEVPOLL EVBACKEND_PORT 如果默认，那么ev会自动判断系统环境，选择最适合的模型，Linux一般为epoll bsd一般为kqueue什么的。
    ev_io stdin_watcher;
    ev_init(&stdin_watcher,stdin_callback);
    ev_io_set(&stdin_watcher,STDIN_FILENO,EV_READ|EV_WRITE);
    ev_io_start(main_loop,&stdin_watcher);

    //ev_run(main_loop,EVRUN_ONCE);

    //void ev_set_io_collect_interval (EV_P_ ev_tstamp interval);//这个是设置轮询的时间
    //typedef double ev_tstamp
    ev_set_io_collect_interval(main_loop,2.);//2秒
    ev_run(main_loop,0);
    //ev_is_active(ev_TYPE * watcher);//用于判断watcher是否为active
    printf("main:%d\n",ev_is_active(&stdin_watcher));

    //initialiased.调用init函数初始化
    //active.调用start进行注册
    //pending.已经触发事件但是没有处理
    //inactive.调用stop注销。这个状态等同于initialised这个状态

    return 0;
}