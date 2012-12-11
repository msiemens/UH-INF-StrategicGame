file(GLOB_RECURSE this "*.cpp")
add_library(server ${this})
target_link_libraries(server gamemodel)