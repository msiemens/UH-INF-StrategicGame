cmake_minimum_required (VERSION 2.6)
project (StrategicGame)

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
target_link_libraries(xclient client gamemodel network ${LINK_WIN32} SDLmain SDL)