//
// Created by Andrew Beck on 1/20/17.
//

#include "ABApp.h"
#include <map>
#include <cstdlib>
#include "ABVertexArray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include "../messaging/ABSocket.h"

using namespace ZeroEngine;

class MatrixPositions {
public:
  MatrixPositions(const glm::mat4x4& start, const glm::mat4x4& end)
      : s(start)
      , e(end) {
  }

  glm::mat4x4 Pos(float a) const {
    return glm::interpolate(s, e, a);
  }

private:
  const glm::mat4x4 s;
  const glm::mat4x4 e;
};


auto appLookupMap = std::map<GLFWwindow*, App*>();
void zeroKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  std::map<GLFWwindow*, App*>::iterator i = appLookupMap.find(window);
  if (i != appLookupMap.end()) {
    ((App*) i->second)->KeyCallback(key, scancode, action, mods);
  }
}

void zeroWindowSizeChangedCallback(GLFWwindow* window, int width, int height) {
  std::map<GLFWwindow*, App*>::iterator i = appLookupMap.find(window);
  if (i != appLookupMap.end()) {
    ((App*) i->second)->WindowSizeChangedCallback(width, height);
  }
}

void zeroRegisterWindow(GLFWwindow* window, App* app) {
  appLookupMap[window] = app;
  glfwSetKeyCallback(window, zeroKeyCallback);
  glfwSetWindowSizeCallback(window, zeroWindowSizeChangedCallback);
}

void zeroUnregisterWindow(GLFWwindow *window) {
  if (appLookupMap.find(window) != appLookupMap.end()) {
    appLookupMap.erase(window);
  }
}

// This is the callback we'll be registering with GLFW for errors.
// It'll just print out the error to the STDERR stream.
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

float randFloat(float min, float max, int precision = 10000) {
  auto scaled = (rand() % precision) / ((float) precision);
  return min + (scaled*(max-min));
}

App::App(int windowWidth, int windowHeight, const char* windowTitle)
    : width(windowWidth)
    , height(windowHeight) {
  // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
  if (!glfwInit()) {
    fprintf(stderr, "Failed initialize GLFW.");
    exit(EXIT_FAILURE);
  }

  // Set the error callback, as mentioned above.
  glfwSetErrorCallback(error_callback);

  // Set up OpenGL options.
  // Use OpenGL verion 4.1,
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Make the window resize-able.
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create a window to put our stuff in.
  window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);


  // If the window fails to be created, print out the error, clean up GLFW and exit the program.
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Use the window as the current context (everything that's drawn will be place in this window).
  glfwMakeContextCurrent(window);
  zeroRegisterWindow(window, this);

  WindowSizeChangedCallback(windowWidth, windowHeight);
}

App::~App() {
  zeroUnregisterWindow(window);
}

void App::Run() {
  printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

  // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
  glewExperimental = GL_TRUE;
  glewInit();

  // Shaders is the next part of our program. Notice that we use version 410 core. This has to match our version of OpenGL we are using, which is the core profile in version 4.1, thus 410 core.

  // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
  // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
  static const char * vs_source[] =
      {
          "#version 410 core                                                 \n"
              "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
              "uniform mat4 mvp;\n"
              "out vec4 pos;\n"
              "void main() {\n"
              "  gl_Position = mvp*vec4(vertexPosition_modelspace,1);"
              "  pos = gl_Position;\n"
              "}\n"
      };

  // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
  static const char * fs_source[] =
      {
          "#version 410 core                                                 \n"
              "                                                                  \n"
              "out vec4 color;                                                   \n"
              "in vec4 pos;\n"
              "                                                                  \n"
              "void main(void)                                                   \n"
              "{                                                                 \n"
              "    color = vec4(abs(pos.z)/16, 0.0, 0.0, 1.0);                             \n"
              "}                                                                 \n"
      };

  // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
  program = glCreateProgram();

  // We create a shader with our fragment shader source code and compile it.
  auto fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, fs_source, NULL);
  glCompileShader(fs);


  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Check Vertex Shader
  glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(fs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("Fragment Shader Error: %s\n", &VertexShaderErrorMessage[0]);
  }


  // We create a shader with our vertex shader source code and compile it.
  auto vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, vs_source, NULL);
  glCompileShader(vs);


  // Check Vertex Shader
  glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("Vertex Shader Error: %s\n", &VertexShaderErrorMessage[0]);
  }

  // We'll attach our two compiled shaders to the OpenGL program.
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &Result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    printf("Program Error: %s\n", &ProgramErrorMessage[0]);
  }

// Camera matrix
  auto View = glm::lookAt(
      glm::vec3(8,6,6),
      glm::vec3(0,0,0), // and looks at the origin
      glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
  );

//  auto modelTransforms = std::vector<MatrixPositions>();
//
//  for (auto i = 0; i < 100; i++) {
//    //auto translationMatrixS = glm::translate(glm::vec3(randFloat(-10, 10), randFloat(-10, 10), randFloat(-10, 10)));
//    //auto rotationMatrixS = glm::rotate(randFloat(-90, 90), glm::vec3(0, 1, 0));
//    //auto scalingMatrixS = glm::mat4x4(1.0f);// glm::scale(glm::vec3(randFloat(0.5, 2), randFloat(0.5, 2), randFloat(0.5, 2)));
//    auto start = glm::mat4x4(1.0f);//translationMatrixS * rotationMatrixS * scalingMatrixS;
//
//    auto translationMatrixE = glm::translate(glm::vec3(randFloat(-10, 10), randFloat(-10, 10), randFloat(-10, 10)));
//    auto rotationMatrixE = glm::rotate(randFloat(-90, 90), glm::vec3(0, 1, 0)) * glm::rotate(randFloat(-90, 90), glm::vec3(1, 0, 0)) * glm::rotate(randFloat(-90, 90), glm::vec3(0, 0, 1));
//    auto scalingMatrixE = glm::mat4x4(1.0f);//glm::scale(glm::vec3(randFloat(0.5, 2), randFloat(0.5, 2), randFloat(0.5, 2)));
//    auto end = translationMatrixE * rotationMatrixE * scalingMatrixE;
//
//    modelTransforms.push_back(MatrixPositions(start,end));
//  }

  auto MatrixID = glGetUniformLocation(program, "mvp");

// Send our transformation to the currently bound shader, in the "MVP" uniform
// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)



  auto array = new VertexArray();

  // We'll specify that we want to use this program that we've attached the shaders to.
  glUseProgram(program);

  float runningI = -1;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

  auto socket = Socket("5555");

  auto objects = std::vector<glm::mat4x4>();

  // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
  while(!glfwWindowShouldClose(window)) {
    auto newWorld = socket.Receive();
    if (newWorld) {
      objects.clear();

      for_each(newWorld->objects().begin(), newWorld->objects().end(), [&objects] (const Object& object) {
        auto translationMatrix = glm::translate(glm::vec3(
            object.position().x(),
            object.position().y(),
            object.position().z()
        ));
        auto rotationMatrix =
            glm::rotate(object.rotation().x(), glm::vec3(1, 0, 0))
            * glm::rotate(object.rotation().y(), glm::vec3(0, 1, 0))
            * glm::rotate(object.rotation().z(), glm::vec3(0, 0, 1));
        auto scalingMatrix = glm::mat4x4(1.0f);//glm::scale(glm::vec3(randFloat(0.5, 2), randFloat(0.5, 2), randFloat(0.5, 2)));

        objects.push_back(translationMatrix * rotationMatrix * scalingMatrix);
      });
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    runningI += 0.01;
    if (runningI >= 1) {
      runningI -= 2.0f;
    }
    auto absI = fabsf(runningI);

    for_each(objects.begin(), objects.end(), [&] (const glm::mat4x4& matrix) {
// Our ModelViewProjection : multiplication of our 3 matrices
      auto mvp = projection * View * matrix; //model.Pos(absI); // Remember, matrix multiplication is the other way around
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
      array->Draw();
    });

    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Program clean up when the window gets closed.
  delete array;
  glDeleteProgram(program);
}

void App::DoSomething(std::function<void (const std::string&)> func) {
  if (func) {
    func(std::string("HELLO WORLD\n"));
  }
}

// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void App::KeyCallback(int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void App::WindowSizeChangedCallback(int windowWidth, int windowHeight) {
  width = windowWidth;
  height = windowHeight;
  projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);


// Or, for an ortho camera :
//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
}