include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  pgx_tests
  pgx_test.cpp
)

target_link_libraries(
  pgx_tests
  CREGEX_FILES
  GTest::gtest_main
)

target_include_directories(pgx_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)
include(CTest)

gtest_discover_tests(pgx_tests)
