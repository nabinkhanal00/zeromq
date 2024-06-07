#include <zmq.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    void *context = zmq_ctx_new();
    void *requestor = zmq_socket(context, ZMQ_REQ);

    zmq_connect(requestor, "tcp://localhost:5555");

    for (int request_nbr = 0; request_nbr < 10; request_nbr++)
    {
        zmq_msg_t request;
        zmq_msg_init_size(&request, 5);
        memcpy(zmq_msg_data(&request), "HeLlO", 5);
        zmq_msg_send(&request, requestor, 0);
        zmq_msg_close(&request);

        zmq_msg_t reply;
        zmq_msg_init(&reply);
        int size = zmq_msg_recv(&reply, requestor, 0);
        char *message = (char *)zmq_msg_data(&reply);
        message[size] = '\0';
        printf("Received %s %d\n", message, request_nbr);
        zmq_msg_close(&reply);
    }
    sleep(2);
    zmq_close(requestor);
    zmq_ctx_destroy(context);
    return 0;
}