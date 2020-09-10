cmake_minimum_required(VERSION 3.11.0)
project(core)

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+$")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

if(EMSCRIPTEN)
    set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1" CACHE STRING "")
endif(EMSCRIPTEN)

file(GLOB_RECURSE COMMON_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE COMMON_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${PROJECT_NAME} ${COMMON_SOURCE_FILES})
add_library(strife::core ALIAS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    strife::common
)

if(EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1"
    )
endif()