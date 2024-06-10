#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();

    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_connect(responder, "tcp://localhost:5560");

    while (1)
    {
        char *msg = s_recv(responder);
        printf("Received request [%s]\n", msg);
        free(msg);
        sleep(1);
        s_send(responder, "WORLD");
    }
    zmq_close(responder);
    zmq_ctx_destroy(context);
}