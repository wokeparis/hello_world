#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/unistd.h>
#include <ev.h>


void io_action(struct ev_loop *main_loop,ev_io *io_w,int e)
{
    int rst;
    char buf[1024];
    memset(buf,0,sizeof(buf));
    puts("In IO action");
    read(STDIN_FILENO,buf,sizeof(buf));
    buf[1023]='\0';
    printf("String: %s\n",buf);
    ev_io_stop(main_loop,io_w);
}

void timer_action(struct ev_loop *main_loop,ev_timer *time_w,int e)
{
    puts("In Time action");
    ev_timer_stop(main_loop,time_w);
}

void signal_action(struct ev_loop *main_loop,ev_signal *signal_w,int e)
{
    puts("In Signal action");
    ev_signal_stop(main_loop,signal_w);
    ev_break(main_loop,EVBREAK_ALL);
}

int main(int argc,char **argv)
{
    ev_io io_w;
    ev_timer timer_w;
    ev_signal signal_w;
    struct ev_loop *main_loop = ev_default_loop(0);

    ev_init(&io_w,io_action);
    ev_io_set(&io_w,STDIN_FILENO,EV_READ);

    ev_init(&timer_w,timer_action);
    ev_timer_set(&timer_w,2,0);

    ev_init(&signal_w,signal_action);
    ev_signal_set(&signal_w,SIGINT);

    ev_io_start(main_loop,&io_w);
    ev_timer_start(main_loop,&timer_w);
    ev_signal_start(main_loop,&signal_w);

    ev_run(main_loop,0);
    return 0;
}