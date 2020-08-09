cmake_minimum_required(VERSION 3.11.0)
project(strife)

if(EMSCRIPTEN)
    set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake")
endif(EMSCRIPTEN)

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+$")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

if(EMSCRIPTEN)
    link_directories(${Boost_LIBRARY_DIRS})
    set(Boost::system libboost_system.a)
    set(Boost::filesystem libboost_filesystem.a)
else()
    find_package(Boost 1.72.0 REQUIRED)
endif()

add_subdirectory(reflection)
add_subdirectory(math)
add_subdirectory(common)
add_subdirectory(serialization)
add_subdirectory(core)
add_subdirectory(main)

add_executable(index main.cpp)

target_compile_features(index INTERFACE cxx_std_17)

target_link_libraries(index
    strife::reflection
    strife::math
    strife::common
    strife::serialization
    strife::core
    strife::main
)

if(EMSCRIPTEN)
    set_target_properties(index PROPERTIES
        SUFFIX ".html"
        LINK_FLAGS "-s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1"
    )
endif()