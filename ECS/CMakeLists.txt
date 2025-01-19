cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0091 NEW)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.6.2 COMPONENTS graphics window system audio REQUIRED)
find_package(Lua REQUIRED)

file(GLOB_RECURSE COMPONENTS_SOURCES
    "src/Components/*/*.cpp"
)

add_executable(MyProject
    ${COMPONENTS_SOURCES}
    src/Main.cpp
    src/Application/Application.cpp
    src/ECS/ECS.cpp
    src/ComponentManager/ComponentManager.cpp
    src/Systems/Systems.cpp
    src/Systems/Systems.hpp
    include/Interface/ISystems.hpp
    include/Abstract/ASystems.hpp
    include/Abstract/ASystems.cpp
)

target_include_directories(MyProject PUBLIC include/Interface)
target_include_directories(MyProject PUBLIC include/Abstract)
target_include_directories(MyProject PRIVATE src/Components)

target_include_directories(MyProject PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(MyProject PRIVATE ${LUA_LIBRARIES})
target_include_directories(MyProject PRIVATE src)
target_link_libraries(MyProject PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
