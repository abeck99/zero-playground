#include <stdio.h>
#include "engine/ABApp.h"

int main() {
  auto app = ZeroEngine::App(800, 600, "OpenGL");
  app.Run();

  app.DoSomething([](const std::string &s) { printf("%s", s.c_str()); });
}