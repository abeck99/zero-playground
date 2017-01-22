cmake_minimum_required(VERSION 3.6)
project(haskell_game_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/protos/world.pb.cc
    src/engine/ABApp.cpp
    src/main.cpp src/engine/ABVertexArray.cpp src/messaging/ABSocket.cpp src/messaging/ABSocket.h)

add_executable(haskell_game_engine ${SOURCE_FILES})

find_library(FOUNDATION Foundation)
find_library(OPEN_GL OpenGL)
find_library(COCOA Cocoa)
find_library(IOKIT IOKit)
find_library(CORE_VIDEO CoreVideo)

target_link_libraries(haskell_game_engine glfw3)
target_link_libraries(haskell_game_engine glew)
target_link_libraries(haskell_game_engine zmq)
target_link_libraries(haskell_game_engine protobuf)
target_link_libraries(haskell_game_engine ${FOUNDATION})
target_link_libraries(haskell_game_engine ${OPEN_GL})
target_link_libraries(haskell_game_engine ${COCOA})
target_link_libraries(haskell_game_engine ${IOKIT})
target_link_libraries(haskell_game_engine ${CORE_VIDEO})
