#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

int main(void) {
    // create a new zeromq context
    void* context = zmq_ctx_new();

    // create a socket and bind to a port
    void* responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    while(1) {
        zmq_msg_t request;
        zmq_msg_init(&request);
        int size      = zmq_msg_recv(&request, responder, 0);
        char* message = (char*)zmq_msg_data(&request);
        message[size] = '\0';
        printf("Received %s\n", (char*)zmq_msg_data(&request));
        zmq_msg_close(&request);

        sleep(1);

        zmq_msg_t reply;
        zmq_msg_init_size(&reply, 5);
        memcpy(zmq_msg_data(&reply), "WORLD", 5);
        zmq_msg_send(&reply, responder, 0);
        zmq_msg_close(&reply);
    }
}
