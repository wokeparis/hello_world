/*************************************************************************
	> File Name: libev_sample_easy.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 24 Dec 2019 12:50:49 AM PST
 ************************************************************************/

#include <iostream>
#include <ev.h>
#include <stdio.h>
using namespace std;
ev_io stdin_watcher;
ev_timer timeout_watcher;

static void stdin_cb(EV_P_ ev_io *w, int revents)
{
    puts("stdin ready");
    ev_io_stop(EV_A_ w);
    ev_break(EV_A_ EVBREAK_ALL);
}

static void timeout_cb(EV_P_ ev_timer *w, int revents)
{
    puts("timeout");
    ev_break(EV_A_ EVBREAK_ONE);
}

int main(int argc, char **args)
{
    struct ev_loop *loop = EV_DEFAULT;

    ev_io_init(&stdin_watcher, stdin_cb, 0, EV_READ);
    ev_io_start(loop, stdin_watcher);

    ev_run(loop, 0);
    return 0;
}
