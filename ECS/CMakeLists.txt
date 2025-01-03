cmake_minimum_required(VERSION 3.12)
project(MyProject)

# set(CMAKE_MODULE_PATH ".")
# set(CMAKE_PREFIX_PATH "C:/Users/Hardeol/Downloads/SFML")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#     add_compile_options(-std=c++20)
# endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include_directories(glm INTERFACE "C:/Users/Hardeol/Downloads/glm")
# include_directories("C:/Users/Hardeol/Downloads/SFML/include")
# find_package(SFML 3 COMPONENTS graphics window system REQUIRED)

add_executable(MyProject
    src/Main.cpp
    src/Application/Application.cpp
    src/ECS/ECS.cpp
    src/Scene/Scene.cpp
    src/ComponentManager/ComponentManager.cpp
    src/ComponentManager/Components.cpp
    src/Systems/Systems.cpp
    src/Systems/Systems.hpp
    include/Interface/ISystems.hpp
    include/Abstract/ASystems.hpp
    include/Abstract/ASystems.cpp
)

target_include_directories(MyProject PUBLIC include/Interface)
target_include_directories(MyProject PUBLIC include/Abstract)
target_include_directories(MyProject PRIVATE src)
target_link_libraries(MyProject PRIVATE sfml-graphics sfml-window sfml-system)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
