cmake_minimum_required(VERSION 3.0)
project(Serialization)

set(SOURCES
    src/main.cpp
    src/Binary.cpp
    src/XML.cpp
    lib/tinyxml2.cpp
)

# 设置头文件文件夹
set(HEADERS
    include/Binary.h
    include/XML.h
    lib/tinyxml2.h
)


# 添加可执行文件
add_executable(Serialization ${SOURCES} ${HEADERS})

# 添加头文件路径
target_include_directories(Serialization PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 链接所需的库
target_link_libraries(Serialization PRIVATE ${LIBRARIES})
