//
// Created by Andrew Beck on 1/20/17.
//

#include "ABApp.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../protos/Person.capnp.h"

using namespace ZeroEngine;

// This is the callback we'll be registering with GLFW for errors.
// It'll just print out the error to the STDERR stream.
void app_error_callback(int error, const char* description) {
  fputs(description, stderr);
}

App::App(int windowWidth, int windowHeight, const char* windowTitle) {

}

void App::DoSomething(std::function<void (const std::string&)> func) {
  if (func) {
    func(std::string("HELLO WORLD\n"));
  }
}
