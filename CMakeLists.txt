cmake_minimum_required(VERSION 3.16)

project(Weather)

add_definitions(-DQT_MESSAGELOGCONTEXT)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Svg REQUIRED)

file(GLOB SOURCE_FILES "*.cpp")
file(GLOB HEADER_FILES "*.hpp")

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Xml
    Qt5::Network
    Qt5::Svg
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
