cmake_minimum_required(VERSION 3.16)

project(rate_limiter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Enable CTest
enable_testing()


# ==========================================
# MAIN APPLICATION
# ==========================================

add_executable(rate_limiter

    src/main.cpp

    src/TokenBucket.cpp
    src/SlidingWindow.cpp
    src/RateLimiter.cpp
    src/Database.cpp

    src/routes/RateLimitController.cpp
    src/routes/AdminController.cpp
)


# ==========================================
# TOKEN BUCKET TEST
# ==========================================

add_executable(token_bucket_test

    tests/TokenBucketTest.cpp

    src/TokenBucket.cpp
)


# ==========================================
# SLIDING WINDOW TEST
# ==========================================

add_executable(sliding_window_test

    tests/SlidingWindowTest.cpp

    src/SlidingWindow.cpp
)


# ==========================================
# CONCURRENCY TEST
# ==========================================

add_executable(ConcurrencyTest

    tests/ConcurrencyTest.cpp

    src/TokenBucket.cpp
)


# ==========================================
# REGISTER TESTS WITH CTEST
# ==========================================

add_test(
    NAME TokenBucketTest
    COMMAND token_bucket_test
)

add_test(
    NAME SlidingWindowTest
    COMMAND sliding_window_test
)

add_test(
    NAME ConcurrencyTest
    COMMAND ConcurrencyTest
)