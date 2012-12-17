cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (StrategicGame)

include_directories("${PROJECT_SOURCE_DIR}")

# Compiler options
add_definitions(-std=gnu++0x)

# OS specific settings
if(WIN32)
	set(LINK_WIN32 "mingw32")
endif()

# External libs
## Include BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.52.0 COMPONENTS system serialization thread)
include_directories("${Boost_INCLUDE_DIRS}")

## Include SDL
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED) # if using SDL_image

include_directories("${SDL_INCLUDE_DIR}")
include_directories("${SDLIMAGE_INCLUDE_DIR}")

message("Include Path is: ${CMAKE_INCLUDE_PATH}")


# Our libs
add_subdirectory(gamemodel)
add_subdirectory(network)
add_subdirectory(server)
add_subdirectory(client)

# Executables
add_executable(xclient client/GameClient)
target_link_libraries(xclient client gamemodel network ${Boost_LIBRARIES} ${LINK_WIN32} ${SDLIMAGE_LIBRARY} ${SDLMAIN_LIBRARY} ${SDL_LIBRARY})

add_executable(xserver server/GameServer)
target_link_libraries(xserver server gamemodel network ${Boost_LIBRARIES} ${LINK_WIN32})