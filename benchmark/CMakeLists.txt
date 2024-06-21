find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(pgx_benchmark pgx_benchmark.cpp)
target_link_libraries(pgx_benchmark benchmark::benchmark ${GTEST_LIBRARIES} pthread CREGEX_FILES)