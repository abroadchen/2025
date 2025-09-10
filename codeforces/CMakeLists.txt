cmake_minimum_required(VERSION 3.29)
project(codeforces)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(codeforces
    src/C.cpp
        src/Winner2A.cpp
        src/Theleastroundway2B.cpp
        src/Commentatorproblem2C.cpp
        src/Shortestpathoftheking3A.cpp
        src/Lorry3B.cpp
        src/Tic-tac-toe3C.cpp)
