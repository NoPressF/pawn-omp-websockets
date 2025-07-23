cmake_minimum_required(VERSION 3.19)
project(websockets LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(sdk)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/pawn/source
    ${CMAKE_CURRENT_SOURCE_DIR}/pawn/source/linux
)

add_definitions(
    -DHAVE_STDINT_H=1
    -DPAWN_CELL_SIZE=32
)

if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /w ")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -static-libgcc -w -fPIC ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -static-libgcc -static-libstdc++ -w -fPIC ")
endif()

if(UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

# Boost for UNIX
if(UNIX)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_ARCHITECTURE "-x32")
    find_package(Boost REQUIRED COMPONENTS thread system)

    if(Boost_FOUND)
        message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
        include_directories(${Boost_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "Boost not found!")
    endif()
endif()

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OMP-SDK
)

if(WIN32)
    find_library(BOOST_THREAD_LIB NAMES libboost_thread-clangw19-mt-x32-1_86 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
    find_library(BOOST_CHRONO_LIB NAMES libboost_chrono-clangw19-mt-x32-1_86 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libs)

    target_link_libraries(${PROJECT_NAME}
   	PRIVATE
        ${BOOST_THREAD_LIB}
        ${BOOST_CHRONO_LIB}
    )
endif()

# Boost for UNIX
if(UNIX)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            Threads::Threads
            ${Boost_LIBRARIES}
    )
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY PREFIX "")
