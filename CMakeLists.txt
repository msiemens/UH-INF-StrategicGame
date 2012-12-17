cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (StrategicGame)

## COMPILER OPTIONS
add_definitions(-std=gnu++0x)

## INCLUDE BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.52.0 COMPONENTS system serialization thread)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(gamemodel)
add_subdirectory(network)
add_subdirectory(server)
add_subdirectory(client)

message("Boost libraries: ${Boost_LIBRARIES}")

# Executables
add_executable(xserver server/GameServer)
target_link_libraries(xserver server gamemodel network ${LINK_WIN32})

add_executable("xnetserver" test/network/server.cpp)
target_link_libraries("xnetserver" network ${Boost_LIBRARIES} mswsock) # TODO: Include mswsock only on MinGW systems

add_executable("xnetclient" test/network/client.cpp)
target_link_libraries("xnetclient" network ${Boost_LIBRARIES} mswsock) # TODO: Include mswsock only on MinGW systems