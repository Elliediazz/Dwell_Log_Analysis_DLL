cmake_minimum_required(VERSION 3.10)
project(DwellLogAnalysis CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/helpers
)

# Source files
set(SOURCES
    main.cpp
    src/DwellLogData.cpp
    src/Analysis.cpp
    helpers/LoadCSV.cpp
)

# Create executable
add_executable(dwell_log_app ${SOURCES})
