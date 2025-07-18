cmake_minimum_required(VERSION 3.16)
project(SFML-Tutorial LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(tutorial_exec src/main.cpp)
target_link_libraries(tutorial_exec PRIVATE sfml-graphics)
target_compile_features(tutorial_exec PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET tutorial_exec
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:tutorial_exec>
        VERBATIM)
endif()

install(TARGETS tutorial_exec)
