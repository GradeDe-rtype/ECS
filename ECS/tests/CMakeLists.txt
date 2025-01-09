# Tests CMakeLists.txt

# ---- SOURCES ---- #
file(GLOB TEST_SOURCES "*.cpp")

# ---- SRC SOURCES ---- #
set(SRC_SOURCES
)

foreach(FILE ${TEST_SOURCES} ${SRC_SOURCES})
    if (NOT EXISTS "${FILE}")
        message(FATAL_ERROR "Source file not found: ${FILE}")
    endif()
endforeach()

# ---- EXECUTABLE ---- #
add_executable(r-type_tests ${TEST_SOURCES} ${SRC_SOURCES})

# ---- INCLUDES ---- #
target_include_directories(r-type_tests PRIVATE
    ${CRITERION_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIR}
)

find_package(SFML 3 COMPONENTS graphics window system REQUIRED)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found or graphics component is unsupported")
endif()

# ---- LINK LIBRARIES ---- #
target_link_libraries(r-type_tests PRIVATE
    ${CRITERION_LIBRARIES}
    ${LUA_LIBRARIES}
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
)

# ---- TESTS ---- #
enable_testing()

# ---- ADD TEST ---- #
add_test(
    NAME MyProjectTests
    COMMAND $<TARGET_FILE:r-type_tests>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# ---- MANUAL TESTS EXECUTION ---- #
add_custom_target(run_tests
    COMMAND $<TARGET_FILE:r-type_tests>
    DEPENDS r-type_tests
    COMMENT "Running Criterion tests"
    VERBATIM
)
