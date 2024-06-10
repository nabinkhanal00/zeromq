#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();

    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5559");

    int request_nbr = 0;
    for (; request_nbr < 10; request_nbr++)
    {
        char *content;
        sprintf(content, "HELLO %d", request_nbr);
        s_send(requester, content);
        char *message = s_recv(requester);
        printf("Received reply [%d] [%s]\n", request_nbr, message);
        free(message);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);
}