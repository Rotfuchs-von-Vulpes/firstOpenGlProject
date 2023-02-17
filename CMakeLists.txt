cmake_minimum_required(VERSION 3.14)
project(game)

# c lang version
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# compiler
set(CMAKE_AR      "D:/Program Files/LLVM/bin/llvm-ar")
set(CMAKE_LINKER  "D:/Program Files/LLVM/bin/llvm-ld")
set(CMAKE_NM      "D:/Program Files/LLVM/bin/llvm-nm")
set(CMAKE_OBJDUMP "D:/Program Files/LLVM/bin/llvm-objdump")
set(CMAKE_RANLIB  "D:/Program Files/LLVM/bin/llvm-ranlib")

# executable
file(GLOB GAME_SRC src/main.c)
add_executable(game src/main.c)


