cmake_minimum_required(VERSION 3.14)
project(SFML_Test)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(my_game main.cpp)
target_link_libraries(my_game PRIVATE sfml-graphics sfml-window sfml-system)

# --- THE NEW AUTOMAGIC PART ---
# This tells CMake: "After you build my_game.exe, go grab all the Windows .dll 
# files SFML needs and drop them directly next to the executable."
add_custom_command(TARGET my_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:my_game> $<TARGET_FILE_DIR:my_game>
    COMMAND_EXPAND_LISTS
)