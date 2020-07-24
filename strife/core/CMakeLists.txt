cmake_minimum_required(VERSION 3.10.0)
project(core)

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

file(GLOB core_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
file(GLOB core_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(${PROJECT_NAME} ${core_SOURCE_FILES})
add_library(strife::core ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME}
        libboost_system.a
        libboost_filesystem.a
        strife::common
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Boost::system
        Boost::filesystem
        strife::common
    )
endif()

install(TARGETS core DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${core_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core)