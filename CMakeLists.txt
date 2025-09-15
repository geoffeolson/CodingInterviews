cmake_minimum_required(VERSION 3.25)

# Project name
project(CodingInterviews LANGUAGES CXX)

# Require C++20 (adjust if needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the single source file
add_executable(${PROJECT_NAME}
    LeetCode/max_profit2.cpp  "LeetCode/max_profit2.cpp" "LeetCode/max_profit2.cpp")

# If you have headers in the LeetCode folder, add that directory
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LeetCode
)

# MSVC-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /EHsc)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()
