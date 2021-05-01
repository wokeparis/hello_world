#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ev.h>

static void three_second_callback(struct ev_loop *loop,ev_timer *w,int revents)
{
    //这是一个3秒触发的计时器
    printf("3秒触发器\n");
}
static void five_second_callback(struct ev_loop *loop,ev_timer *w,int revents)
{
    //这是一个5秒触发的计时器
    printf("5秒触发器\n");
}
static void the_second_callback(struct ev_loop *loop,ev_timer *w,int revents)
{
    //这是一个10秒触发的计时器
    printf("10秒触发器\n");
}

int main(int argc, char **args)
{
    struct ev_loop * main_loop=ev_default_loop(0);

    ev_timer mytimer_watcher3;
    ev_timer mytimer_watcher5;

    ev_init(&mytimer_watcher3,three_second_callback);
    ev_timer_set(&mytimer_watcher3,3,0);
    ev_timer_start(main_loop,&mytimer_watcher3);
    ev_run(main_loop,0);//这个在ev_io上是一直判断的。但是这个触发器只会触发一次，不会每3秒触发一次。这是个问题。

    ev_init(&mytimer_watcher5,five_second_callback);
    ev_timer_set(&mytimer_watcher5,5,0);
    ev_timer_start(main_loop,&mytimer_watcher5);
    ev_run(main_loop,0);


    ev_timer_start(main_loop,&mytimer_watcher3);
    ev_timer_start(main_loop,&mytimer_watcher5);
    ev_run(main_loop,0);//这里不会等待3，5秒，而是上一步后，直接输出,可见触发器只能用一次

    ev_timer_set(&mytimer_watcher3,3,0);
    ev_timer_start(main_loop,&mytimer_watcher3);
    ev_timer_set(&mytimer_watcher5,5,0);
    ev_timer_start(main_loop,&mytimer_watcher5);
    ev_run(main_loop,0);//这里就会等待了，要重新set一遍


    return 0;
}