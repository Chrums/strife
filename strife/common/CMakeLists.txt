cmake_minimum_required(VERSION 3.11.0)
project(common)

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+$")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

if(EMSCRIPTEN)
    set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1" CACHE STRING "")
endif(EMSCRIPTEN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2" CACHE STRING "")

if(EMSCRIPTEN)
    link_directories(${Boost_LIBRARY_DIRS})
else()
    find_package(Boost 1.72.0 REQUIRED COMPONENTS
        filesystem
        system
    )
endif()

file(GLOB_RECURSE COMMON_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE COMMON_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${PROJECT_NAME} ${COMMON_SOURCE_FILES})
add_library(strife::common ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME}
        libboost_system.a
        libboost_filesystem.a
        nlohmann_json::nlohmann_json
        strife::math
        "-s USE_SDL=2"
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Boost::system
        Boost::filesystem
        nlohmann_json::nlohmann_json
        strife::math
    )
endif()

if(EMSCRIPTEN)
    set_target_properties(common PROPERTIES
        LINK_FLAGS "-s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0"
    )
endif()