#include "zhelpers.h"
#include "zmq.h"

int main()
{
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    int rc = zmq_connect(receiver, "tcp://localhost:5557");
    assert(rc == 0);

    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5558");

    while (1)
    {
        char *string = s_recv(receiver);
        printf("%s.", string);
        fflush(stdout);

        // Do the work
        s_sleep(atoi(string));
        free(string);
        s_send(sender, "");
    }
    zmq_close(sender);
    zmq_close(receiver);
    zmq_ctx_destroy(context);
}
