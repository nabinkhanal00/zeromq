#include "zhelpers.h"
#include <stdbool.h>

int main() {
    void* context = zmq_ctx_new();
    assert(context);

    void* publisher = zmq_socket(context, ZMQ_PUB);
    assert(publisher);

    int rc = zmq_bind(publisher, "tcp://*:5563");
    assert(rc == 0);

    while(true) {
        s_sendmore(publisher, "A");
        s_send(publisher, "We would not like to see this.");

        s_sendmore(publisher, "B");
        s_send(publisher, "We would like to see this.");
        sleep(1);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(publisher);

    return 0;
}
