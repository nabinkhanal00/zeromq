#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();

    void *publisher = zmq_socket(context, ZMQ_PUB);

    int rc = zmq_bind(publisher, "tcp://*:5566");
    assert(rc == 0);

    rc = zmq_bind(publisher, "ipc://weather.ipc");
    assert(rc == 0);

    srandom( (unsigned)time(NULL));

    while(1){
        int zipcode, temperature, relhumidity;
        zipcode = randof(1000000);
        temperature = randof(215) - 80;
        relhumidity = randof(50) + 10;

        char update[20];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send(publisher, update);

    }
    zmq_close(publisher);
    zmq_ctx_destroy(context);
}