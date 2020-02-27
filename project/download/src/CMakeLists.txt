cmake_minimum_required (VERSION 2.8)

project (DownLoad)

aux_source_directory(. DIR_SRCS)

add_executable(Download ${DIR_SRCS})

target_link_libraries(Download ssl crypto pthread)
