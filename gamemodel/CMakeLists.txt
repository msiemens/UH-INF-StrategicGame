add_subdirectory(actions)
add_subdirectory(entities)
add_subdirectory(ressources)
add_subdirectory(utils)

file(GLOB this "*.h" "*.cpp")
add_library(gamemodel, ${this})