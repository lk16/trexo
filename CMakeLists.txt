cmake_minimum_required(VERSION 2.8)

project(trexo)

find_package(PkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

set(FLAGS
	" -fdiagnostics-color -std=c99 -I -pthread -Wall -Wmissing-prototypes -Wstrict-prototypes -Wextra -Wfloat-equal -Wno-unused-result -Wshadow -Wstrict-aliasing -pipe"
)

set(DEBUG_FLAGS "${FLAGS} -g")
set(OPTMISING_FLAGS "${FLAGS} -O3 -fforce-addr -ftree-vectorize -funroll-loops")

set(CMAKE_C_FLAGS 
	#${OPTMISING_FLAGS}
	${DEBUG_FLAGS}
) 

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})


file(GLOB SOURCE_FILES
    "src/*.c"
)

add_executable(trexo
  ${SOURCE_FILES}
)
target_link_libraries(trexo
  	${GTK3_LIBRARIES}
  	${GLIB_LIBRARIES}
)
