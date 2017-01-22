//
// Created by Andrew Beck on 1/20/17.
//

#ifndef HASKELL_GAME_ENGINE_ABVERTEXARRAY_H
#define HASKELL_GAME_ENGINE_ABVERTEXARRAY_H

#include <GL/glew.h>

namespace ZeroEngine {
  class VertexArray {
  public:
    VertexArray();
    ~VertexArray();

    void Draw();
  private:
    GLuint vao;
    GLuint vbo;
  };
}

#endif //HASKELL_GAME_ENGINE_ABVERTEXARRAY_H
