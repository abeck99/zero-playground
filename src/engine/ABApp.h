//
// Created by Andrew Beck on 1/20/17.
//

#ifndef PROJECT_ABAPP_H
#define PROJECT_ABAPP_H

#include <string>
#include <functional>

namespace ZeroEngine {
  class App {
  public:
    App(int windowWidth, int windowHeight, const char* windowTitle);
    void DoSomething(std::function<void (const std::string&)> func);
  };
}

#endif //PROJECT_ABAPP_H
