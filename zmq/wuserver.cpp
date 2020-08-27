




/*************************************************************************
	> File Name: wuserver.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 26 Dec 2019 11:01:12 PM PST
 ************************************************************************/

#include <iostream>
#include "zhelpers.h"
using namespace std;

int main(void)
{
    void *context = zmq_init(1);
    void *publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5566");
    zmq_bind(publisher, "ipc://weather.ipc");
    srandom ((unsigned) time (NULL));
    while (1) {
        //  生成数据
        int zipcode, temperature, relhumidity;
        zipcode     = randof (100000);
        temperature = randof (215) - 80;
        relhumidity = randof (50) + 10;

        //  向所有订阅者发送消息
        char update [20];
        sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send (publisher, update);
    }
    zmq_close (publisher);
    zmq_term (context);
    return 0;

}
