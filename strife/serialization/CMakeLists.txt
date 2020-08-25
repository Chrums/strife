cmake_minimum_required(VERSION 3.11.0)
project(serialization)

include(FetchContent)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.9.0
)

FetchContent_GetProperties(json)

if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+$")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

if(EMSCRIPTEN)
    set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1" CACHE STRING "")
endif(EMSCRIPTEN)

if(EMSCRIPTEN)
    link_directories(${Boost_LIBRARY_DIRS})
else()
    find_package(Boost 1.72.0 REQUIRED COMPONENTS
        filesystem
        system
    )
endif()

file(GLOB_RECURSE SERIALIZATION_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE SERIALIZATION_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${PROJECT_NAME} ${SERIALIZATION_SOURCE_FILES})
add_library(strife::serialization ALIAS ${PROJECT_NAME})

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
        strife::common
        strife::reflection
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Boost::system
        Boost::filesystem
        nlohmann_json::nlohmann_json
        strife::math
        strife::common
        strife::reflection
    )
endif()