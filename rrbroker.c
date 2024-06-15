#include "zhelpers.h"

int main() {
    void* context = zmq_ctx_new();

    void* frontend = zmq_socket(context, ZMQ_ROUTER);
    void* backend  = zmq_socket(context, ZMQ_DEALER);

    zmq_bind(frontend, "tcp://*:5559");
    zmq_bind(backend, "tcp://*:5560");

    zmq_pollitem_t items[2] = {
        { frontend, 0, ZMQ_POLLIN, 0 },
        { backend, 0, ZMQ_POLLIN, 0 },
    };

    while(1) {
        zmq_msg_t message;
        int more;

        zmq_poll(items, 2, -1);

        if(items[0].revents & ZMQ_POLLIN) {
            while(1) {
                zmq_msg_init(&message);
                zmq_msg_recv(&message, frontend, 0);
                size_t more_size = sizeof(more);
                zmq_getsockopt(frontend, ZMQ_RCVMORE, &more, &more_size);
                zmq_msg_send(&message, backend, more ? ZMQ_SNDMORE : 0);
                zmq_msg_close(&message);
                if(!more) {
                    break;
                }
            }
        }
        if(items[1].revents & ZMQ_POLLIN) {
            while(1) {
                zmq_msg_init(&message);
                zmq_msg_recv(&message, backend, 0);
                size_t more_size = sizeof(more);
                zmq_getsockopt(backend, ZMQ_RCVMORE, &more, &more_size);
                zmq_msg_send(&message, frontend, more ? ZMQ_SNDMORE : 0);
                zmq_msg_close(&message);
                if(!more) {
                    break;
                }
            }
        }
    }
    zmq_close(frontend);
    zmq_close(backend);
    zmq_ctx_destroy(context);
    return 0;
}
