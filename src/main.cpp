#include <stdio.h>
#include "engine/ABApp.h"

class X {
	public:
  X() {}

      	int test() const { return 1;}
};

int main() {
  const X* p, q;
  p = new X();

  printf("p: %d, q: %d\n", p->test(), q.test());

  auto app = ZeroEngine::App(800, 600, "OpenGL");
  app.Run();

  app.DoSomething([](const std::string &s) { printf("%s", s.c_str()); });
}
