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
# OS specific settings
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
	set(LINK_WIN32 "mingw32")
endif()

# Our libs
add_subdirectory(gamemodel)
add_subdirectory(network)
add_subdirectory(server)
add_subdirectory(client)

# External libs
set(SDL_PATH CACHE PATH "Path do SDL libs.")
set(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH}:${SDL_PATH}/include")
set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}:${SDL_PATH}/lib")
set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}:${SDL_PATH}/lib")


# Executables
add_executable(xclient client/GameClient)
target_link_libraries(xclient client gamemodel network ${LINK_WIN32} SDL_image SDLmain SDL)
add_subdirectory(client)

message("Boost libraries: ${Boost_LIBRARIES}")

# Executables
add_executable(xserver server/GameServer)
target_link_libraries(xserver server gamemodel network ${LINK_WIN32})

add_executable("xnetserver" test/network/server.cpp)
target_link_libraries("xnetserver" network ${Boost_LIBRARIES} mswsock) # TODO: Include mswsock only on MinGW systems

add_executable("xnetclient" test/network/client.cpp)
target_link_libraries("xnetclient" network ${Boost_LIBRARIES} mswsock) # TODO: Include mswsock only on MinGW systems