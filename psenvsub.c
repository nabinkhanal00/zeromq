#include "zhelpers.h"

int main(int argc, char** argv) {
    int rc;

    void* context = zmq_ctx_new();
    assert(context);

    void* subscriber = zmq_socket(context, ZMQ_SUB);
    assert(subscriber);

    rc = zmq_connect(subscriber, "tcp://localhost:5563");
    assert(rc == 0);

    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, argv[1], 1);
    assert(rc == 0);

    while(1) {
        char* address = s_recv(subscriber);
        char* content = s_recv(subscriber);
        printf("[%s] [%s]\n", address, content);
        free(address);
        free(content);
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}
