#include "zhelpers.h"

int main() {
  void *context = zmq_ctx_new();

  void *request = zmq_socket(context, ZMQ_REQ);

  zmq_connect(request, "tcp://localhost:5556");

  while (1) {
    s_send(request, "Hello");
    char *msg = s_recv(request);
    printf("Received: [%s]\n", msg);
    free(msg);
    sleep(1);
  }
  zmq_close(request);
  zmq_ctx_destroy(context);
}