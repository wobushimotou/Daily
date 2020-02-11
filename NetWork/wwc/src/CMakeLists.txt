cmake_minimum_required(VERSION 3.10)

project (Server)

aux_source_directory(. DIR_SRCS)

add_subdirectory(poll)

add_executable(Server ${DIR_SRCS})

target_link_libraries(Server PollFunctions pthread)


