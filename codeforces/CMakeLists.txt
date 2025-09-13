cmake_minimum_required(VERSION 3.29)
project(codeforces)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(src)

add_executable(codeforces
    src/C.cpp
        src/Winner2A.cpp
        src/Theleastroundway2B.cpp
        src/Commentatorproblem2C.cpp
        src/Shortestpathoftheking3A.cpp
        src/Lorry3B.cpp
        src/Tic-tac-toe3C.cpp
        src/LeastCostBracketSequence3D.cpp
        src/Watermelon4A.cpp
        src/BeforeanExam4B.cpp
        src/Registrationsystem4C.cpp
        src/MysteriousPresent4D.cpp
        src/ChatServer'sOutgoingTraffic5A.cpp
        src/CenterAlignment5B.cpp
        src/LongestRegularBracketSequence5C.cpp
        src/FollowTrafficRules5D.cpp
        src/BindianSignalizing5E.cpp
        src/Triangle6A.cpp
        src/President'sOffice6B.cpp
        src/Alice,BobandChocolate6C.cpp
        "src/LizardsandBasements6D .cpp"
        src/Exposition6E.cpp
        src/KalevitchandChess7A.cpp
        src/MemoryManager7B.cpp
        src/Line7C.cpp
        src/PalindromeDegree7D.cpp
        src/DefiningMacros7E.cpp
        src/TrainandPeter8A.cpp
        src/ObsessionwithRobots8B.cpp
        src/LookingforOrder8C.cpp
        src/TwoFriends8D.cpp
        src/Beads8E.cpp)

set_target_properties(codeforces PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
