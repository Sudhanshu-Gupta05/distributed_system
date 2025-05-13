cmake_minimum_required(VERSION 3.10)
project(s3_service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    storage_service.cpp
    in_memory_storage_strategy.cpp
    s3_object.cpp
    notification_service.cpp
    main.cpp
)

# Header files
set(HEADERS
    storage_service.hpp
    storage_strategy.hpp
    in_memory_storage_strategy.hpp
    s3_object.hpp
    notification_service.hpp
)

# Create executable
add_executable(s3_service ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(s3_service PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 