cmake_minimum_required (VERSION 2.6)
project (StrategicGame)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(gamemodel)
add_subdirectory(network)
add_subdirectory(server)
add_subdirectory(client)