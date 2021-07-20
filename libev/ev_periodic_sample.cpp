#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ev.h>

static void periodic_callback(struct ev_loop *loop,ev_periodic * w, int revents)
{
    printf("每3秒执行一次\n");
    //ev_break(loop,EVBREAK_ALL);
}

//ev_tstamp=double
static ev_tstamp periodic_scheduler_callback(ev_periodic *w,ev_tstamp now)
{
    return now+3;//注意时间要加上个now，是一个绝对时间
}

int main(int argc, char **args)
{
    struct ev_loop * main_loop=ev_default_loop(0);

    ev_periodic periodic_watcher;
    //下面这个是第3个参数为3 是一个表达式
    ev_init(&periodic_watcher,periodic_callback);
    ev_periodic_set(&periodic_watcher,0,3,0);
    ev_periodic_start(main_loop,&periodic_watcher);
    ev_run(main_loop,0);

    //如果时间周期计算方式，不能通过一个表达式来表示，那么可以通过一个函数来表示，放在set的第4个参数
    ev_init(&periodic_watcher,periodic_callback);
    ev_periodic_set(&periodic_watcher,0,0,periodic_scheduler_callback);
    ev_periodic_start(main_loop,&periodic_watcher);
    ev_run(main_loop,0);
    //注意上下两部分不能通过运行，要注释掉一个才可以看到效果
    return 0;
}