//
// Created by Andrew Beck on 1/20/17.
//

#ifndef PROJECT_ABAPP_H
#define PROJECT_ABAPP_H

#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

namespace ZeroEngine {
  class App {
  public:
    App(int windowWidth, int windowHeight, const char* windowTitle);
    ~App();

    void Run();

    void DoSomething(std::function<void (const std::string&)> func);

    void KeyCallback(int key, int scancode, int action, int mods);
    void WindowSizeChangedCallback(int windowWidth, int windowHeight);

  private:
    GLFWwindow* window;
    GLuint program;

    glm::mat4x4 projection;
    int width;
    int height;

  };

}

#endif //PROJECT_ABAPP_H
