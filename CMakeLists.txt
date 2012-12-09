cmake_minimum_required (VERSION 2.6)
project (StrategicGame)

include_directories(${PROJECT_SOURCE_DIR})

# OS specific settings
if(WIN32)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
set(LINK_WIN32 "mingw32")
endif()

add_subdirectory(gamemodel)
add_subdirectory(network)
add_subdirectory(server)
add_subdirectory(client)


# Executables
add_executable(xserver server/GameServer)
target_link_libraries(xserver gamemodel network ${LINK_WIN32})