cmake_minimum_required(VERSION 3.11.0)
project(strife)

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+$")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

if(EMSCRIPTEN)
    set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1" CACHE STRING "")
endif(EMSCRIPTEN)

add_subdirectory(common)
add_subdirectory(core)

add_executable(index main.cpp)

set_property(TARGET index PROPERTY CXX_STANDARD 20)
target_compile_features(index INTERFACE cxx_std_20)

target_link_libraries(index
    strife::common
    strife::core
)

if(EMSCRIPTEN)
    set_target_properties(index PROPERTIES
        # SUFFIX ".html"
        LINK_FLAGS "-s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1"
    )
endif()