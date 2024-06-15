#include "zhelpers.h"

int main() {
  void *context = zmq_ctx_new();

  void *reply = zmq_socket(context, ZMQ_REP);

  zmq_connect(reply, "tcp://localhost:5555");
  while (1) {

    char *msg = s_recv(reply);
    printf("Received: [%s]\n", msg);

    free(msg);
    s_send(reply, "World");
  }
  zmq_close(reply);
  zmq_ctx_destroy(context);
}
