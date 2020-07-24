cmake_minimum_required(VERSION 3.10.0)
project(common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

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
else()
    find_package(Boost 1.72.0 REQUIRED COMPONENTS
        filesystem
        system
    )
endif()

file(GLOB COMMON_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
file(GLOB COMMON_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(${PROJECT_NAME} ${COMMON_SOURCE_FILES})
add_library(strife::common ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME}
        libboost_system.a
        libboost_filesystem.a
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Boost::system
        Boost::filesystem
    )
endif()

install(TARGETS common DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${COMMON_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/common)