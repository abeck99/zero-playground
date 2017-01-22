//
// Created by Andrew Beck on 1/21/17.
//

#ifndef HASKELL_GAME_ENGINE_ABSOCKET_H
#define HASKELL_GAME_ENGINE_ABSOCKET_H

#include "zmq.h"
#include "../protos/world.pb.h"

#define SOCKET_PROTOCOL "tcp://127.0.0.1:"

namespace ZeroEngine {
  class Socket {
  public:
    Socket(const char* socketName);

    std::unique_ptr<World> Receive();

  private:
    void* socket;
  };
}


#endif //HASKELL_GAME_ENGINE_ABSOCKET_H
