cmake_minimum_required(VERSION 3.19)
project(websockets LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sdk)
add_subdirectory(network)

link_directories(libs)

include_directories(
	.
	pawn/source
	pawn/source/linux
)

add_definitions(
	-DHAVE_STDINT_H=1
	-DPAWN_CELL_SIZE=32
)

if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /w")
else()
	set(CMAKE_C_FLAGS "-m32 -static-libgcc -w")
	set(CMAKE_CXX_FLAGS "-m32 -static-libgcc -static-libstdc++ -w ")
endif()

# Boost
if(UNIX)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_ARCHITECTURE "-x32")

	find_package(Boost REQUIRED COMPONENTS REQUIRED)

	if(Boost_FOUND)
		include_directories(${Boost_INCLUDE_DIRS})
	else(Error)
		message(FATAL_ERROR "Boost can not be found!")
	endif()
endif()

file(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
	OMP-SDK
	${Boost_LIBRARIES}
)
