#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();

    void *sender = zmq_socket(context, ZMQ_PUSH);
    int rc = zmq_bind(sender, "tcp://*:5557");
    assert(rc == 0);

    void *sink = zmq_socket(context, ZMQ_PUSH);
    rc = zmq_connect(sink, "tcp://localhost:5558");
    assert(rc == 0);

    printf("Enter when the workers are ready: ");
    getchar();
    printf("Sending tasks to workers...\n");

    s_send(sink, "0");

    srandom((unsigned)time(NULL));

    int total_msec = 0; // total expected cost in msec

    for (int task_nbr = 0; task_nbr < 100; task_nbr++)
    {
        int workload = randof(10) + 1;
        total_msec += workload;
        char string[10];
        sprintf(string, "%d", workload);
        s_send(sender, string);
    }
    printf("Total expected cost: %d msec\n", total_msec);
    getchar();
    zmq_close(sink);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;
}
