cmake_minimum_required(VERSION 3.16)
project(mtm_ex3_partC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic-errors -Werror")
link_directories(.)
add_executable(mtm_ex3_partC main.cpp Character.cpp Soldier.cpp Sniper.cpp Medic.cpp Game.cpp Exceptions.cpp)
target_link_libraries(mtm_ex3_partC )