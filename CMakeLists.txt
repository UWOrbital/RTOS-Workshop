# cmake_minimum_required(VERSION 3.15)

# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain_gcc.cmake)

# project(workshop)

# if(CMAKE_BUILD_TYPE MATCHES SCHEDULING)
#     set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#     enable_language(C CXX)
#     add_subdirectory(scheduling)
# else()
#     message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
# endif()

# add_subdirectory(freertos)
# target_link_libraries(scheduling.out PRIVATE
#     FreeRTOS
#     Threads::Threads
# )
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)
cmake_minimum_required(VERSION 3.15)

enable_language(C CXX)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain_gcc.cmake)

project(workshop)

if(CMAKE_BUILD_TYPE MATCHES SCHEDULING)
    set(SOURCES
        scheduling.c
    )
elseif(CMAKE_BUILD_TYPE MATCHES MUTEX)
    set(SOURCES
        mutex.c
    )
elseif(CMAKE_BUILD_TYPE MATCHES QUEUE)
    set(SOURCES
        queue.c
    )
else()
    message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

add_executable(workshop ${SOURCES})

target_compile_options(workshop PRIVATE -O0)

target_include_directories(workshop PRIVATE
)

add_subdirectory(freertos)
target_link_libraries(workshop PRIVATE
FreeRTOS
Threads::Threads
)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
