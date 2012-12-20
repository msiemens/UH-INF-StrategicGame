file(GLOB_RECURSE this "*.cpp")
add_library(network ${this})
target_link_libraries(network gamemodel ${Boost_LIBRARIES} ${LINK_WIN32})
