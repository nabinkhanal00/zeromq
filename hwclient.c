#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    void *requestor = zmq_socket(context, ZMQ_REQ);

    zmq_connect(requestor, "tcp://localhost:5555");

    for (int request_nbr = 0; request_nbr < 10; request_nbr++)
    {
        char *msg;
        sprintf(msg, "HELLO %d", request_nbr);
        s_send(requestor, msg);
        char *message = s_recv(requestor);
        printf("Received %s %d\n", message, request_nbr);
        free(message);
    }
    sleep(2);
    zmq_close(requestor);
    zmq_ctx_destroy(context);
    return 0;
}
