cmake_minimum_required(VERSION 3.11.0)
project(math)

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

FetchContent_Declare(eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.3.7
)

FetchContent_GetProperties(eigen)
if(NOT eigen_POPULATED)
    FetchContent_Populate(eigen)
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

file(GLOB_RECURSE MATH_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE MATH_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${PROJECT_NAME} ${MATH_SOURCE_FILES})
add_library(strife::math ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${eigen_SOURCE_DIR}
)

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME}
        nlohmann_json::nlohmann_json
    )
else()
    target_link_libraries(${PROJECT_NAME}
        nlohmann_json::nlohmann_json
    )
endif()