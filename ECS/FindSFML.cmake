# SFML Configuration File
set(SFML_INCLUDE_DIR "C:/Users/Hardeol/Downloads/SFML/include")
set(SFML_LIB_DIR "C:/Users/Hardeol/Downloads/SFML/lib")

# set(SFML_INCLUDE_DIR "/home/aeliondw/SFML/include")
# set(SFML_LIB_DIR "/home/aeliondw/SFML/lib")

# Specify SFML libraries
set(SFML_LIBRARIES
    ${SFML_LIB_DIR}/libsfml-graphics.a
    ${SFML_LIB_DIR}/libsfml-window.a
    ${SFML_LIB_DIR}/libsfml-system.a
)

# Export variables for CMake
set(SFML_FOUND TRUE)
set(SFML_VERSION "3.1.0")

# Set include directories and libraries
set(SFML_INCLUDE_DIRS ${SFML_INCLUDE_DIR})
set(SFML_LIBRARY_DIRS ${SFML_LIB_DIR})
