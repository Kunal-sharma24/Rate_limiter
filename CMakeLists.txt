cmake_minimum_required(VERSION 3.16)

project(rate_limiter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Main application
add_executable(rate_limiter

    src/main.cpp

    src/TokenBucket.cpp
    src/SlidingWindow.cpp
    src/RateLimiter.cpp
    src/Database.cpp

    src/routes/RateLimitController.cpp
    src/routes/AdminController.cpp
)