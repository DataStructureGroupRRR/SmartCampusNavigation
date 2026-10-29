cmake_minimum_required(VERSION 3.10)
project(SmartCampusNavigation)

set(EXECUTABLE_NAME ${PROJECT_NAME})

set(SOURCE_FILES
    "src/main.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")