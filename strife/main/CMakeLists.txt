cmake_minimum_required(VERSION 3.11.0)
project(main)

include(FetchContent)

FetchContent_Declare(bullet
    GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
    GIT_TAG 2.89
)

FetchContent_GetProperties(bullet)
if(NOT bullet3_POPULATED)
    FetchContent_Populate(bullet)
    add_subdirectory(${bullet_SOURCE_DIR} ${bullet_BINARY_DIR} EXCLUDE_FROM_ALL)
    target_include_directories(Bullet3Common INTERFACE
        ${bullet_SOURCE_DIR}/src
    )
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

file(GLOB_RECURSE MAIN_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE MAIN_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${PROJECT_NAME} ${MAIN_SOURCE_FILES})
add_library(strife::main ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME}
        libboost_system.a
        libboost_filesystem.a
        Bullet3Collision
        Bullet3Common
        Bullet3Dynamics
        Bullet3Geometry
        BulletCollision
        BulletDynamics
        BulletInverseDynamics
        BulletSoftBody
        LinearMath
        strife::common
        strife::core
        strife::math
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Boost::system
        Boost::filesystem
        Bullet3Common
        Bullet3Dynamics
        strife::common
        strife::core
        strife::math
    )
endif()

if(EMSCRIPTEN)
    set_target_properties(main PROPERTIES
        LINK_FLAGS "-s WASM=1 -s DEMANGLE_SUPPORT=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0"
    )
endif()