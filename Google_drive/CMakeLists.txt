cmake_minimum_required(VERSION 3.10)
project(FileSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files
set(SOURCES
    main.cpp
    FileSystemManager.cpp
    Folder.cpp
    File.cpp
    User.cpp
    PermissionsDecorator.cpp
    FileSystemProxy.cpp
    CreateFileOperation.cpp
    FileOperation.cpp
    FileSystemSearch.cpp
    LocalStorageStrategy.cpp
    Subject.cpp
    FileVersion.cpp
)

# Add all header files
set(HEADERS
    FileSystemManager.hpp
    Folder.hpp
    File.hpp
    User.hpp
    PermissionsDecorator.hpp
    FileSystemProxy.hpp
    CreateFileOperation.hpp
    FileOperation.hpp
    FileSystemSearch.hpp
    LocalStorageStrategy.hpp
    StorageStrategy.hpp
    Subject.hpp
    Observer.hpp
    FileVersion.hpp
    FileSystemComponent.hpp
)

# Create executable
add_executable(filesystem ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(filesystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 