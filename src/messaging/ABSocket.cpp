//
// Created by Andrew Beck on 1/21/17.
//

#include "ABSocket.h"
#include <assert.h>
#include <capnp/serialize.h>

#define CONNECT_RETRIES 5


#ifdef DEBUG_ASSERT
#   define ASSERT(condition, message) { if ( !(condition) ) { breakHere(); printf("`" #condition "` failed in %s line %d : `" #message "`\n", __FILE__, __LINE__ ); STACK_TRACE_TO_STD_ERR; std::exit(EXIT_FAILURE); } }
#else
#   define ASSERT(condition, message)
#endif

void* gContext = zmq_ctx_new();

using namespace ZeroEngine;

Socket::Socket(const char* socketName)
  : socket(zmq_socket(gContext, ZMQ_SUB)) {
  char socketAddress[512];
  sprintf(socketAddress, "%s%s", SOCKET_PROTOCOL, socketName);

  int rc = 1;
  int numTries = 0;
  while ( (numTries++) < CONNECT_RETRIES )
  {
    rc = zmq_bind(socket, socketAddress);
    if ( rc == 0 )
      break;
    else
      printf("binding %s, errno: %u\n", socketAddress, errno);
  }
  ASSERT (rc == 0, "Bind failed!");

  zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);    // no filter
}

std::unique_ptr<World> Socket::Receive() {
  int rc;
  zmq_msg_t* msg = new zmq_msg_t;
  bool hasMessage = false;

  rc = zmq_msg_init (msg);
  assert (rc == 0);

  bool cont = true;
  while (cont) {
    zmq_msg_t currentMessage;
    rc = zmq_msg_init(&currentMessage);
    assert (rc == 0);

    rc = zmq_msg_recv(&currentMessage, socket, ZMQ_DONTWAIT);

    if (rc >= 0) {
      hasMessage = true;
      rc = zmq_msg_copy(msg, &currentMessage);
      assert(rc == 0);
    } else if (errno == EAGAIN) {
      cont = false;
    } else {
      printf("Error receiving: %d\n", rc);
      cont = false;
    }

    zmq_msg_close(&currentMessage);
  }

  if (hasMessage) {
    auto world = new World();
    if (world->ParseFromArray(zmq_msg_data(msg), zmq_msg_size(msg))) {
      zmq_msg_close(msg);
      return std::unique_ptr<World>(world);
    }

    printf("Failed to get message, it was sized: %lu\n", zmq_msg_size(msg));

    delete world;
  }

  zmq_msg_close(msg);
  return nullptr;
}
