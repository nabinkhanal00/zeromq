#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();

    int update_nbr = 100;
    printf("Calculating average temperature of %d days:\n", update_nbr);
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, "ipc://weather.ipc");
    printf("Connected to the server...\n");
    assert(rc == 0);
    const char *filter = "10001";
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));
    assert(rc == 0);

    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++)
    {
        char *string = s_recv(subscriber);
        int zipcode, temperature, relhumidity;
        sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
        total_temp += temperature;
        free(string);
    }
    printf("Average temperature for zipcoe '%s' was %dF\n", filter, (int)(total_temp / update_nbr));
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}