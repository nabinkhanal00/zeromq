#include "zhelpers.h"

int main() {
  void *context = zmq_ctx_new();

  void *frontend = zmq_socket(context, ZMQ_ROUTER);
  void *backend = zmq_socket(context, ZMQ_DEALER);

  zmq_bind(backend, "tcp://localhost:5555");
  zmq_bind(frontend, "tcp://localhost:5556");
  zmq_proxy(frontend, backend, 0);

  zmq_close(frontend);
  zmq_close(backend);
  zmq_ctx_destroy(context);
}
